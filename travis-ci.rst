========================================
Travis CI
========================================

Notification
========================================

* `Travis CI - Notification <http://docs.travis-ci.com/user/notifications/>`_

Gitter
------------------------------

.. code-block:: yaml

    notifications:
      webhooks:
        urls:
          - YOUR_WEBHOOK_URL
        on_success: change  # options: [always|never|change] default: always
        on_failure: always  # options: [always|never|change] default: always
        on_start: false     # default: false

Samples
========================================

* `Neovim <https://github.com/neovim/neovim/blob/master/.travis.yml>`_
    - C
    - Multiple Build
    - Multiple Test
