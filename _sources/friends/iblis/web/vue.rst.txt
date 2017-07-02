Vue
===============================================================================

- MVVM pattern


Vue Instance
----------------------------------------------------------------------

- ``data`` property proxy

- properties created by vue will be prefixed with ``$``.
  e.g.: ``vm.$el``, ``vm.$watch``

- Instance hook: ``mounted`` ... etc.


Slots
----------------------------------------------------------------------

Child component::

    div
      h2 I'm the child title

      slot
      | This will only be displayed
      | if there is no content to be distributed.  // fallback content

Parent::
    div
      h1 I'm the parent title

      child-component
        p This is some original content
        p This is some more original content

Render::

    div
      h1 I'm the parent title

      div
        h2 I'm the child title

        p This is some original content
        p This is some more original content
