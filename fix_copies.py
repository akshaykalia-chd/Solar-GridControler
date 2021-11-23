import os
import random
from os.path import exists

os.chdir("..")

def get_files():
    f = open("./Arduino/file_list.txt")
    lines = f.readlines()
    f.close()
    files = list()
    for line in lines:
        line = line.rstrip('\n')
        files.append(line)
    return files


def rename_file(src, dst):
    file_exists = exists(dst)
    if file_exists:
        digit = str(random.randint(0, 99))
        print(dst + "is all ready present")
        dst = dst + "_" + digit
        print("File is all ready present renaming to " + dst)
        os.rename(src, dst)
    else:
        os.rename(src, dst)


def get_dst(src: str = None) -> str:
    try:
        dst = src.split('-')
        dst = dst[0].strip(" ") + "." + dst[1].split('.')[1].strip(" ")
        return dst
    except IndexError:
        print("Error processing file:"+src)
        dst = src.replace('-','_',1)
        dst = dst.split('-')
        dst = dst[0].strip(" ") + "." + dst[1].split('.')[1].strip(" ")
        return dst


files = get_files()
for file in files:
    dst = (get_dst(file))
    rename_file(file,dst)

