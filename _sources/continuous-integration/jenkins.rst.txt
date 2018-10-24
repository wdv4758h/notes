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



Declarative Jenkinsfile
========================================

Pipeline
------------------------------

Node
------------------------------

Parameters Build
------------------------------

範例
------------------------------

.. code-block:: Jenkinsfile

    pipeline {
        agent any
        options {
            timestamps()
            disableConcurrentBuilds()
            // Only keep the 5 most recent builds
            buildDiscarder(logRotator(numToKeepStr: '5'))
        }

        parameters {
            // these will let user input some parameters when triggering build
            string(name: 'BRANCH_PROJ1',
                   defaultValue: 'develop',
                   description: 'PROJ1 build branch')
            string(name: 'BRANCH_PROJ2',
                   defaultValue: 'develop',
                   description: 'PROJ2 build branch')
        }

        environment {
            // define variable
            JOB_SIGNATURE = "${env.JOB_NAME} ${env.BUILD_NUMBER} (${env.BUILD_URL})"
        }

        stages {
            stage("checking out") {
                steps {
                    checkout scm
                }
            }

            stage("check env") {
                steps {
                    script {
                        if (params.foo) {
                            sh "echo foo=${params.foo}"
                        }
                    }
                }
            }

            stage("build projects") {
                steps {
                    script {
                        // use plugin to display terminal color on web
                        ansiColor('xterm') {
                            sh "make all"
                        }
                    }
                }
            }
        }

        post {
            always {
                // docker clean up, avoid eating a lot of disk
                sh "docker system prune -f"
            }

            success {
                slackSend channel: '#jenkins-builds',
                          color: '#90EE90',
                          message: "Yes !! PROJS Build Passed - ${JOB_SIGNATURE}"
            }

            failure {
                slackSend channel: '#jenkins-builds',
                          color: '#b20900',
                          message: "No  !! PROJS Build Failed - ${JOB_SIGNATURE}"
            }
        }
    }



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
