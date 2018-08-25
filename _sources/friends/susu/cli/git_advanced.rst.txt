Git Advanced
============

1. git rebase -i
----------------
``git rebase -i <base> <head>``

operations

- pick
- drop
- reword: 改 commit message, 強化版的 --amend.
- squash, fixup: merge commit
- edit: 修改 commit 內容, 適合需要拆 commit 時使用.
- exec

2. diff/patch tool
------------------

- git diff and apply

  ::

      # 將某些 git commits diff 出來, 並 apply 到 working directory 中.
      git diff <options> > xxx.patch
      git apply xxx.patch
      
      # 放進 stage area 跟 commit 則是之後手動作.
      # 比如可以用 git add -p 分成多個 commits 來存到現在的 branch 裡.

- git format-patch and am

  - 連 git commit message 都有包留的 diff/patch tool
  - ``$ git format-patch <revision_range>``
  - `revision range <https://git-scm.com/book/tr/v2/Git-Tools-Revision-Selection#_commit_ranges>`_

3. more about git log 
----------------------
- git reflog

  - `30 天精通 Git 版本控管 (16)：善用版本日誌 git reflog 追蹤變更軌跡 <http://ithelp.ithome.com.tw/articles/10138150>`_
  - `Gitbook ch9.7: Git Internals - Maintenance and Data Recovery <https://git-scm.com/book/zh-tw/v1/Git-%E5%85%A7%E9%83%A8%E5%8E%9F%E7%90%86-%E7%B6%AD%E8%AD%B7%E5%8F%8A%E8%B3%87%E6%96%99%E5%BE%A9%E5%8E%9F>`_

- git refs

  - .git/refs/heads/, remotes/, tags/
  - `Gitbook v2 Ch10.3: Git Internals - Git References <https://git-scm.com/book/zh-tw/v2/Git-Internals-Git-References>`_
  - `git show-ref <http://git-scm.com/docs/git-show-ref>`_

problems/use case
-----------------
1. different commits between branches
   ::

     # 3 methods to find difference commits between 2 branchs devel and next
     # find the commits in devel but doesn't merge to next

     # 1.
     git checkout devel
     git cherry next
     # 2.
     git log --oneline devel ^next
     # 3.
     git log next..devel

   - https://stackoverflow.com/questions/7566416/how-to-see-which-commits-in-one-branch-arent-in-the-other
   - `git cherry - Find commits not merged upstream <http://schacon.github.io/git/git-cherry.html>`_

2. find repo history: https://gist.github.com/u1240976/e3f8cd493e0ac4458b92062321eec6ce
