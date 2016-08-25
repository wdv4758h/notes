BASEDIR=.
OUTPUTDIR=$(BASEDIR)/_build/html/
GITHUB_REPO_SLUG=wdv4758h/notes
GITHUB_REMOTE_NAME=origin
GITHUB_PAGES_BRANCH=gh-pages
# 以上參數請根據需求自行替換
GITHUB_COMMIT_MSG=$(shell git --no-pager log --format=%s -n 1)

sphinx:
	# 使用 README.rst 作為 index.rst
	mv README.rst index.rst

	# 用 Sphinx 編出網頁
	sphinx-build -T -E -b readthedocs -d _build/doctrees-readthedocs -D language=zh_TW . _build/html

push: sphinx
	# 為 Travis CI 設定 git 的 user.name 和 user.email
	# 沒設定 email 的話，GitHub 上面看到的 Author 會是 Unknown
	git config --global user.name "wdv4758h - Travis"
	git config --global user.email wdv4758h@gmail.com

	# 將 Sphinx output dir 的內容 commit 到 GitHub Pages 用的 branch，準備 push 上去
	# user site 的 branch 是 master，project site 的 branch 是 gh-pages
	ghp-import -n -r $(GITHUB_REMOTE_NAME) -b $(GITHUB_PAGES_BRANCH) -m "$(GITHUB_COMMIT_MSG)" $(OUTPUTDIR)

	# 將剛剛的 commit push 到 GitHub 上相同的 branch
	@if [ -z ${GH_TOKEN} ]; then echo "GH_TOKEN is unset"; else echo "GH_TOKEN is set"; fi
	@git push -fq https://${GH_TOKEN}@github.com/$(GITHUB_REPO_SLUG).git $(GITHUB_PAGES_BRANCH):$(GITHUB_PAGES_BRANCH) > /dev/null
	# 用 @ 可以讓 Travis CI 不要顯示這行在 log 上，這樣別人就不會看到你的 GitHub Personal Access Token 了，也就是這裡用的 GH_TOKEN

travis: push
