#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/pagemap.h>

#define LFS_MAGIC 0x19980122

static atomic_t counter;

static struct inode *lfs_make_inode(struct super_block *sb, int mode)
{
	struct inode *ret = new_inode(sb);

	if (ret == NULL) {
		pr_err("new_inode failed\n");
		return -ENOMEM;
	}

	ret->i_mode = mode;
	ret->i_uid = ret->i_gid = 0;
	ret->i_blksize = PAGE_CACHE_SIZE;
	ret->blocks = 0;
	ret->i_atime = ret->i_mtime = ret->i_ctime = CURRENT_TIME;

	return ret;
}

static struct file_operations lfs_file_ops = {
	.open  = lfs_open,
	.read  = lfs_read_file,
	.write = lfs_write_file,
};

static struct dentry *lfs_create_file(struct super_block *sb,
		struct dentry *dir, const char *name,
		atomic_t *counter)
{
	struct dentry *dentry;
	struct inode *inode;
	struct qstr qname;

	qname.name = name;
	qname.len = strlen(name);
	qname.hash = full_name_hash(name, qname.len);
	dentry = d_alloc(dir, &qname);

	inode = lfs_make_inode(sb, S_IDREG | 0644);
	if (!inode)
		goto out_dput;
	inode->i_fop = &lfs_file_ops;
	inode->u.generic_ip = counter;

	d_add(dentry, inode);
	return dentry;

out_dput:
	dput(dentry);
out:
	return 0;
}

static void lfs_create_files(struct super_block *sb, struct dentry *root)
{
	atomic_set(&counter, 0);
	lfs_create_file(sb, root, "counter", &counter);
}

static struct dentry *lfs_create_dir(struct super_block *sb,
		struct dentry *parent, const char *name)
{
	
}

static struct super_operations lfs_s_ops = {
	.statfs     = simple_statfs,
	.drop_inode = generic_delete_inode,
};

static int lfs_fill_super(struct super_block *sb, void *data, int silent)
{
	struct inode *root;
	struct dentry *root_dentry;

	sb->s_blocksize      = PAGE_CACHE_SIZE;
	sb->s_blocksize_bits = PAGE_CACHE_SHIFT;
	sb->s_magic          = LFS_MAGIC;
	sb->s_op             = &lfs_s_ops;

	root = lfs_make_inode(sb, S_IFDIR | 0755);
	if (!root)
		goto out;
	root->i_op = &simple_dir_inode_operations;
	root->i_fop = &simple_dir_operations;

	root_dentry = d_alloc_root(root);
	sb->s_root = root_dentry;

	lfs_make_files(sb, root_dentry);

	return 0;
out_iput:
	iput(root);
out:
	return -ENOMEM;

}

static struct super_block *lfs_get_super(struct file_system_type *fst,
		int flags, const char *devname, void *data)
{
	return get_sb_single(fst, flags, data, lfs_fill_super);
}

static struct file_system_type lfs_type = {
	.owner   = THIS_MODULE,
	.name    = "lwnfs",
	.get_sb  = lfs_get_super,
	.kill_sb = kill_little_super,
};

static int __init lfs_init(void)
{
	pr_info("lfs module loaded\n");

	return register_filesystem(&lfs_type);
}

static void __exit lfs_exit(void)
{
	pr_info("lfs module unloaded\n");
}

module_init(lfs_init);
module_exit(lfs_exit);

MODULE_AUTHOR("YogaPan <godhand1234567@gmail.com>");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("file system");
