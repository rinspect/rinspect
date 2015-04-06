mv tools/clang ../
find . -regex ".*\.[cChH]\(pp\)?" -print | etags -
mv ../clang tools
