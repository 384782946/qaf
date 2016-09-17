# coding:utf-8

import re,os

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
    for root,dirs,files in os.walk(path):
        for file in files:
            if filter(file):
                file_path = os.path.join(root,file)
                count(file_path)
        for dir in dirs:
            travel(os.path.join(root,dir))

if __name__ == "__main__":
    travel('./')
    print 'file number:',file_num
    print 'line number:',total