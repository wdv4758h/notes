===========================================================
用 Travis CI 自動化發佈 reStructuredText 到 GitHub Pages 上
===========================================================

（以下修改自 m157q 的
`用 Travis CI 自動化發佈 Pelican blog 到 GitHub Pages 上 <https://m157q.github.io/posts/2016/05/08/use-travis-ci-to-publish-pelican-blog-on-github-pages-automatically/>`_
）


我這邊會利用 Sphinx 來幫忙處理 reStructuredText 到 HTML 的轉換


1. 到 ``https://travis-ci.org/profile/${YOUR_GITHUB_USERNAME}`` 把要使用的 repo 打開
2. 設定 ``.travis.yml``

    .. code-block:: yaml

        language: python
        python:
          - '3.5'

        branches:
          only:
              - master  # 我把 reStructuredText 的原始檔放在 master branch

        install:
          - pip install sphinx readthedocs-sphinx-ext sphinx_rtd_theme ghp-import

        script:
          - make travis  # 需要在 Makefile 新增 travis 的 label


3. 設定 ``Makefile``

    .. code-block:: make

        BASEDIR=.
        OUTPUTDIR=$(BASEDIR)/_build/html/
        GITHUB_REPO_SLUG=wdv4758h/notes
        GITHUB_REMOTE_NAME=origin
        GITHUB_PAGES_BRANCH=gh-pages
        # 以上參數請根據需求自行替換
        GITHUB_COMMIT_MSG=$(shell git --no-pager log --format=%s -n 1)

        travis:
        	# 使用 README.rst 作為 index.rst
        	mv README.rst index.rst

        	# 用 Sphinx 編出網頁
        	sphinx-build -T -E -b readthedocs -d _build/doctrees-readthedocs -D language=zh_TW . _build/html

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


4. 設定 Sphinx 的 ``conf.py`` （以下複製自 readthedocs 的設定，可以自己做調整）

    .. code-block:: python

        #!/usr/bin/env python
        # -*- coding: utf-8 -*-

        # This conf.py is modified from readthedocs

        # from recommonmark.parser import CommonMarkParser

        extensions = []
        templates_path = ['templates', '_templates', '.templates']
        source_suffix = ['.rst']
        # source_parsers = { '.md': CommonMarkParser, }
        master_doc = 'index'
        project = u'wdv4758h-notes'
        copyright = u'2016'
        version = 'latest'
        release = 'latest'
        exclude_patterns = ['_build']
        pygments_style = 'sphinx'
        htmlhelp_basename = 'wdv4758h-notes'
        html_theme = 'sphinx_rtd_theme'
        file_insertion_enabled = False
        latex_documents = [
          ('index', 'wdv4758h-notes.tex', u'wdv4758h-notes Documentation',
           u'', 'manual'),
        ]



        ###########################################################################
        #          auto-created readthedocs.org specific configuration            #
        ###########################################################################


        #
        # The following code was added during an automated build on readthedocs.org
        # It is auto created and injected for every build. The result is based on the
        # conf.py.tmpl file found in the readthedocs.org codebase:
        # https://github.com/rtfd/readthedocs.org/blob/master/readthedocs/doc_builder/templates/doc_builder/conf.py.tmpl
        #


        import sys
        import os.path
        from six import string_types

        from sphinx import version_info

        # Get suffix for proper linking to GitHub
        # This is deprecated in Sphinx 1.3+,
        # as each page can have its own suffix
        if globals().get('source_suffix', False):
            if isinstance(source_suffix, string_types):
                SUFFIX = source_suffix
            else:
                SUFFIX = source_suffix[0]
        else:
            SUFFIX = '.rst'

        # Add RTD Static Path. Add to the end because it overwrites previous files.
        if not 'html_static_path' in globals():
            html_static_path = []
        if os.path.exists('_static'):
            html_static_path.append('_static')

        # Add RTD Theme only if they aren't overriding it already
        using_rtd_theme = False
        if 'html_theme' in globals():
            if html_theme in ['default']:
                # Allow people to bail with a hack of having an html_style
                if not 'html_style' in globals():
                    import sphinx_rtd_theme
                    html_theme = 'sphinx_rtd_theme'
                    html_style = None
                    html_theme_options = {}
                    if 'html_theme_path' in globals():
                        html_theme_path.append(sphinx_rtd_theme.get_html_theme_path())
                    else:
                        html_theme_path = [sphinx_rtd_theme.get_html_theme_path()]

                    using_rtd_theme = True
        else:
            import sphinx_rtd_theme
            html_theme = 'sphinx_rtd_theme'
            html_style = None
            html_theme_options = {}
            if 'html_theme_path' in globals():
                html_theme_path.append(sphinx_rtd_theme.get_html_theme_path())
            else:
                html_theme_path = [sphinx_rtd_theme.get_html_theme_path()]
            using_rtd_theme = True

        if globals().get('websupport2_base_url', False):
            websupport2_base_url = 'https://readthedocs.org/websupport'
            if 'http' not in settings.MEDIA_URL:
                websupport2_static_url = 'https://media.readthedocs.org/static/'
            else:
                websupport2_static_url = 'https://media.readthedocs.org//static'


        #Add project information to the template context.
        context = {
            'using_theme': using_rtd_theme,
            'html_theme': html_theme,
            'current_version': "latest",
            'MEDIA_URL': "https://media.readthedocs.org/",
            'PRODUCTION_DOMAIN': "readthedocs.org",
            'versions': [
            ("latest", "/zh_TW/latest/"),
            ],
            'downloads': [
            ("htmlzip", "//readthedocs.org/projects/wdv4758h-notes/downloads/htmlzip/latest/"),
            ],
            'subprojects': [
            ],
            'slug': 'wdv4758h-notes',
            'name': u'wdv4758h-notes',
            'rtd_language': u'zh_TW',
            'canonical_url': 'http://wdv4758h-notes.readthedocs.io/zh_TW/latest/',
            'analytics_code': '',
            'single_version': False,
            'conf_py_path': '/./',
            'api_host': 'https://readthedocs.org',
            'github_user': 'wdv4758h',
            'github_repo': 'notes',
            'github_version': 'master',
            'display_github': True,
            'bitbucket_user': 'None',
            'bitbucket_repo': 'None',
            'bitbucket_version': 'master',
            'display_bitbucket': False,
            'READTHEDOCS': True,
            'using_theme': (html_theme == "default"),
            'new_theme': (html_theme == "sphinx_rtd_theme"),
            'source_suffix': SUFFIX,
            'user_analytics_code': '',
            'global_analytics_code': '',
        }

        if 'html_context' in globals():
            html_context.update(context)
        else:
            html_context = context

        # Add custom RTD extension
        if 'extensions' in globals():
            extensions.append("readthedocs_ext.readthedocs")
        else:
            extensions = ["readthedocs_ext.readthedocs"]


5. 設定 ``GH_TOKEN``

    到 ``https://github.com/settings/tokens`` 點選右上方的 Generate new token，
    select scopes 就點選 repo。

    到 ``https://travis-ci.org/${user_name}/${repo_name}`` ，
    移到右手邊的 more options 並點選 settings。
    底下有個 Environment Variables，有 Name 和 Value 兩個欄位，
    在 Name 欄位填上 ``GH_TOKEN`` ，
    在 Value 欄位貼上剛剛複製的 Token，
    然後點選 Add 即可。


----

#Python
#reStructuredText #rst #Sphinx
#GitHub #GitHub_Pages
#Travis
#readthedocs
#ghp-import
