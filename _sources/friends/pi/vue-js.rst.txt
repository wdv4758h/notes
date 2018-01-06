===============================================================================
Vue.js
===============================================================================
Vue.js 的特色是即時的 data binding，網頁中的多項元素可以「綁定」一些資料，並雙向的更新


Basic
-------------------------------------------------------------------------------
* HTML ::

    <div id="app">
      <p>{{ message }}</p>
      <input v-model="message">
    </div>

* JavaScript ::

    new Vue({
      el: '#app',
      data: {
        message: 'Hello Vue.js!'
      }
    })

``<p>`` 以及 ``<input>`` 的內容將會自動同步


Binding Expressions
-------------------------------------------------------------------------------
若要在 DOM 元素中展開變數，需要一些 template 語法，稱為 binding expressions

寫法和 Mustache template language 類似

* ``<span>{{ message | capitalize | filterA 'arg2' arg3 }}</span>``


Directives
-------------------------------------------------------------------------------
* ``v-model``
* ``v-for``

  - ``<li v-for="a in b">`` 根據 ``a`` 與 ``b`` 的值產生多個 ``<li>``

* ``v-on``

  - ``<button v-on:click="func">Hey</button>``
  - 可用 ``@`` 簡寫： ``<button @click="func">Hey</button>``

* ``v-if`` / ``v-else``

  - 使 DOM 元素根據條件消失/出現
  - 用在 ``<template>`` tag 上可以一次包裝多個 DOM 元素

* ``v-bind``

  - 用來 binding attributes
  - ``<a v-bind:href="url"></a>`` 和 ``<a href="{{ url }}"></a>`` 效果相同
  - 根據變數值調整 class ::

      <div v-bind:class="{'class-a': cond1, 'class-b': cond2}"></div>

    + 可用 ``:class`` 簡寫

  - 根據變數值調整 style ::

      <div v-bind:style="{'border': 'solid 1px '+ color}"></div>

    + 可用 ``:style`` 簡寫

* 自訂 directive ::

    Vue.directive('focus', {
        bind: function () {
            var object = this.el;
            Vue.nextTick(function() {
                object.focus();
            });
        }
    });

  - 產生 ``v-focus`` directive
  - 讓新產生的 ``<input>`` 自動被 focus


Properties
-------------------------------------------------------------------------------
一個 Vue instance 可以帶有許多 properties

* ``computed``

  - 使某些 properties 由一些邏輯產生::

      let vm = new Vue({
        data: {
          foo: 'Foo',
          bar: 'Bar',
        },
        computed: {
          foobar: function () {
            return this.foo + this.bar;
          }
        }
      });

    + getter/setter 都可以為 computed
