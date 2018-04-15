========================================
Neovim Client
========================================


.. contents:: 目錄


Client 和 Neovim 溝通的方式
========================================

Neovim 有提供彈性化撰寫 Plugin 的方式（ ``msgpack RPC API`` ），
只要使用 MessagePack 就可以操控 Neovim 的行為。



Neovim API Info
========================================

.. code-block:: sh

    # Python 3
    # need 'msgpack-python' and 'pyyaml'
    nvim --api-info | python -c "import msgpack, sys, yaml; print(yaml.dump(msgpack.unpackb(sys.stdin.buffer.read(), encoding='ascii')))"



Client 的功能
========================================

Python Client
------------------------------

* [GitHub] `neovim/python-client <https://github.com/neovim/python-client>`_


.. code-block:: python

    import neovim

    @neovim.plugin
    class TestPlugin(object):

        def __init__(self, nvim):
            self.nvim = nvim

        @neovim.function("TestFunction", sync=True)
        def testfunction(self, args):
            return 3

        @neovim.command("TestCommand", range='', nargs='*')
        def testcommand(self, args, range):
            self.nvim.current.line = ('Command with args: {}, range: {}'
                                      .format(args, range))

        @neovim.autocmd('BufEnter', pattern='*.py', eval='expand("<afile>")', sync=True)
        def on_bufenter(self, filename):
            self.nvim.out_write("testplugin is in " + filename + "\n")


.. code-block:: rust

    #[neovim_function, "TestFunction", sync=True]
    fn test_function():
        ...

    #[neovim_command, "TestCommand", range='', nargs='*']
    fn test_command():
        ...

    #[neovim_autocmd, "BufEnter", pattern='*.py', eval='expand("<afile>")', sync=True]
    fn on_bufenter():
        ...


.. code-block:: go

    package main

    import (
        "strings"
        "github.com/neovim/go-client/nvim/plugin"
    )

    func hello(args []string) (string, error) {
        return "Hello " + strings.Join(args, " "), nil
    }

    func main() {
        plugin.Main(func(p *plugin.Plugin) error {
            p.HandleFunction(&plugin.FunctionOptions{Name: "Hello"}, hello)
            return nil
        })
    }



功能
========================================

* attach Neovim
* pass data in msgpack format
* simple interactive shell



參考
========================================
