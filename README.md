# Git上传到分支

1.增加远程地址

git remote add origin https://github.com/9DemonFox/Linux-Advanced-Environment-System.git

2.和远程分支关联

如果远程有该分支，需要当前与其关联
git branch --set-upstream-to origin/google

如果远程没有该分支，需要从本地推送
$ git checkout -b name #(创建并且切换到分支)
$ git push origin GCC-practice:GCC-practice
Username for 'https://github.com': 9DemonFox
Password for 'https://9DemonFox@github.com':
