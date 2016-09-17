# coding:utf-8

import re,os,sys

extens = ['.h','.cpp']

ignores = ['^moc_','^ui_','^qrc_']
ignore_patterns = [ re.compile(ignore) for ignore in ignores]

total = 0
file_num = 0

def filter(path):
    ext = os.path.splitext(path)[-1]
    if not ext in extens:
        return False
    for patten in ignore_patterns:
        if patten.match(path):
            return False
    return True

def count(file_path):
    global total
    global file_num
    with open(file_path) as f:
        total += len(f.readlines())
        file_num += 1

def travel(path):
    for dir in os.listdir(path):
        if os.path.isdir(os.path.join(path,dir)):
            travel(os.path.join(path, dir))
        elif filter(dir):
            count(os.path.join(path,dir))

if __name__ == "__main__":
    if len(sys.argv) > 1:
        travel(sys.argv[1])
    else:
        travel(os.path.curdir)
    print 'file number:',file_num
    print 'line number:',total