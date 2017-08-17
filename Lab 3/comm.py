#!/usr/bin/python

import sys, string, locale
from optparse import OptionParser

locale.setlocale(locale.LC_ALL, 'C')

class comm:
    def __init__(self, f1, f2, o):
        self.file1 = f1
        self.file2 = f2
        self.opts = o

    def compare(self):
        word1 = word2 = 0
        col2 = 1
        col3 = 2
        if self.opts.one: # sets tabs based on options
            col2-=1
            col3-=1
        if self.opts.two:
            col3-=1
        if self.opts.unsorted:
            for word in self.file1: # checks each word in first file to second file
                if self.file2.count(word) == 0 and not self.opts.one:
                    print(word) # if only in first file
                else:
                    while word2 < len(self.file2):
                        if word == self.file2[word2]:
                            if not self.opts.three: # if in both files
                                print(("\t" * col3) + word)
                            self.file2.pop(word2)
                            break
                        word2+=1
                word2 = 0
            for word in self.file2: # prints remaining words in file 2
                if not self.opts.two:
                    print(("\t" * col2) + word)
                        
        else:
            while word1 < len(self.file1) and word2 < len(self.file2):
                if self.file1[word1] == self.file2[word2]: # if line in both files
                    if not self.opts.three:
                        print(("\t" * col3) + self.file1[word1])
                    word1+=1
                    word2+=1
                elif self.file1[word1] > self.file2[word2]: # if file 1 line lexographically later than line in file 2
                    if not self.opts.two:
                        print(("\t" * col2) + self.file2[word2])
                    word2+=1
                else: # if file 2 line lexographically later than line in file 1
                    if not self.opts.one:
                        print(self.file1[word1])
                    word1+=1
            if word1 == len(self.file1): # if file 1 is shorter than file 2, prints out file 2
                if not self.opts.two:
                    while word2 < len(self.file2):
                        print(("\t" * col2) + self.file2[word2])
                        word2+=1
            elif word2 == len(self.file2): # if file 2 shorter than file 1, prints out file 1
                if not self.opts.one:
                    while word1 < len(self.file1):
                        print(self.file1[word1])
                        word1+=1
					
 	

def inputOrFile(file): # creates lists from input or files
    if (file == '-'):
        return list(sys.stdin.read().split('\n'))
    else:
        f = open(file, 'r').read().split('\n')
        return f

def main():
    version_msg = "%prog 1.0"
    usage_msg = """%prog [OPTION]... FILE1... FILE2
    Displays common/different lines between 2 Files."""
    
    parser = OptionParser(version=version_msg, usage=usage_msg)
    parser.add_option("-1", action="store_true", dest="one", default=False, help="Suppress column of lines unique to File 1.")
    parser.add_option("-2", action="store_true", dest="two", default=False, help="Suppress column of lines unique to File 2.")
    parser.add_option("-3", action="store_true", dest="three", default=False, help="Suppress column of lines found in both files.")
    parser.add_option("-u", action="store_true", dest="unsorted", default=False, help="Allow files to be unsorted")
    options, args = parser.parse_args(sys.argv[1:])

    if len(args) != 2:
        parser.error("wrong number of operands")
    try:
        file1 = inputOrFile(args[0])
        file2 = inputOrFile(args[1])
        comm(file1, file2, options).compare()
    except IOError as err:
        errno, strerror = srr.args
        parser.error("I/O error({0}): {1}".format(errno, strerror))

if __name__ == "__main__":
    main()
