cd `dirname $0`

mkdir $1
cd $1
touch a.cpp
touch b.cpp
touch c.cpp
touch d.cpp
touch e.cpp
touch f.cpp
echo -e "# ABC $1\n\n## 重要メモ\n\n## E" > README.md
