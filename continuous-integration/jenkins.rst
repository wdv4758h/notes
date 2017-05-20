========================================
Jenkins
========================================


.. contents:: 目錄


定期掃特定 GitHub Organization
========================================

`github-organization-folder <https://wiki.jenkins-ci.org/display/JENKINS/GitHub+Organization+Folder+Plugin>`_ + `multi-branch <https://wiki.jenkins-ci.org/display/JENKINS/Multi-Branch+Project+Plugin>`_

設定完後就會自動掃 GitHub Organization 的 repo，
只要有符合規則的新 PR 或 Branch 就會觸發 Jenkins 執行，
不同的 Branch 或 PR 會被自動放到不同的資料夾，
另外可以在 ``Jenkinsfile`` 內設定送通知道 Slack 之類的地方通知。
