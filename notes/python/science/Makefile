server:
	python3 -m http.server 8080 > /dev/null 2>&1 &
stop:
	ps aux | grep http.server | cut -d" " -f3 | head -n 1| xargs kill
clean:
	@rm -rf *.png
