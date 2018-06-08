========================================
Jenkins
========================================


.. contents:: 目錄


Jenkins CLI
========================================

.. code-block:: sh

  # example commands:
  # * version
  # * clear-queue
  # * install-plugin <plugin name>
  java -jar jenkins-cli.jar -s http://localhost:8080/ -i .ssh/mykey <command>



定期掃特定 GitHub Organization
========================================

`github-organization-folder <https://wiki.jenkins-ci.org/display/JENKINS/GitHub+Organization+Folder+Plugin>`_ + `multi-branch <https://wiki.jenkins-ci.org/display/JENKINS/Multi-Branch+Project+Plugin>`_

設定完後就會自動掃 GitHub Organization 的 repo，
只要有符合規則的新 PR 或 Branch 就會觸發 Jenkins 執行，
不同的 Branch 或 PR 會被自動放到不同的資料夾，
另外可以在 ``Jenkinsfile`` 內設定送通知道 Slack 之類的地方通知。




With Git Flow
========================================



Pipeline
========================================



Jenkinsfile
========================================

Pipeline
------------------------------

Node
------------------------------


Jenkins X
========================================



一些小 Groovy Scripts
========================================

列出某個 repo 的所有 branch：

.. code-block:: groovy

    def gettags = "git ls-remote git@github.com:USER/REPO.git".execute(null, null)

    return gettags.text.readLines()
              .collect {
                it.split()[1]
                  .replaceAll('\\^\\{\\}', '')
                  .replaceAll('refs/\\w+/', '')
              }


.. code-block:: groovy

    def gettags = "git ls-remote git@github.com:USER/REPO.git".execute(null, null)

    return gettags.text.readLines()
              .collect {
                it.split()[1]
                  .replaceAll('\\^\\{\\}', '')
                  .replaceAll('refs/\\w+/', '')
              }
              .findAll { !it.startsWith("CI-") }



Theme
========================================

* `Jenkins Material Design Theme <https://github.com/afonsof/jenkins-material-theme>`_



參考
========================================

* `Jenkins - Pipeline <https://jenkins.io/doc/pipeline/>`_
* `Jenkins and Python <https://jenkins.io/solutions/python/>`_
