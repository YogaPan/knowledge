import time
from threading import Thread
from queue import Queue

class Mission:
    def __init__(self, max_thread):
        self.queue = Queue()
        self.max_thread = max_thread

    def __enter__(self):
        for x in range(self.max_thread):
            thread = Thread(target=self._threader)
            thread.daemon = True
            thread.start()
        return self

    def __exit__(self, exception_type, exception_value, traceback):
        self.queue.join()

    def send_task(self, func, *args):
        self.queue.put((func, args))

    def _threader(self):
        while True:
            try:
                func, args = self.queue.get()
                func(*args)
                self.queue.task_done()
            except queue.Empty:
                pass

def sleep(sec):
    print("start")
    print(sec)
    time.sleep(sec)
    print("end")
    print(sec)

def mission_test():
    with Mission(5) as m:
        m.send_task(sleep, 5)
        m.send_task(sleep, 4)
        m.send_task(sleep, 3)
        m.send_task(sleep, 2)
        m.send_task(sleep, 1)
        m.send_task(sleep, 1)

mission_test()
