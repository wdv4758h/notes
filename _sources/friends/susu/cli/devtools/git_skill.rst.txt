Git Skills
==========
record some skills I have ever needed, tried, or searched.

- different commits between branches

  - http://stackoverflow.com/questions/7566416/different-commits-between-two-branches
  ::
  
      # two git branch devel and next

      # 1.
      git checkout devel
      git cherry next
      # 2.
      git log --oneline devel ^next
      # 3.
      git log next..devel


internal
--------
- git refs

  - .git/refs/heads/, remotes/, tags/
  - `Git Internals - Git References <https://git-scm.com/book/zh-tw/v2/Git-Internals-Git-References>`_
  - `git show-ref <http://git-scm.com/docs/git-show-ref>`_
