========================================
std::process
========================================


.. contents:: 目錄


使用
========================================

Command ::

    A process builder, providing fine-grained control over how a new process should be spawned.


``std::process::Command`` 實做採用了 Builder pattern，
使用上是直接用 ``new`` 建一個新的，
此時會具有現在程式的環境變數、執行路徑、stdin/stdout/stderr，
建完之後可以再補上想要的參數。

底下是把各平台的 ``Command`` 實做抽開，
在 sys 底下根據各平台特製實做，
``libstd/process.rs`` 把平台特製實做包裝成統一的界面。


實做：

* https://github.com/rust-lang/rust/blob/master/src/libstd/process.rs
* https://github.com/rust-lang/rust/blob/master/src/libstd/sys_common/process.rs
* https://github.com/rust-lang/rust/blob/master/src/libstd/sys/unix/process/process_unix.rs



使用範例：

.. code-block:: rust

    use std::process::{Command, Stdio};         // command builder, stdio control
    use std::os::unix::process::CommandExt;     // Unix-like only methods, e.g. uid, gid

    ////////////////////
    // 執行方式一： .output()

    let output =
        Command::new("echo")
                // 指令參數
                .arg("aaa")
                .arg("bbb")
                .args(&["ccc", "ddd"])
                .arg("eee")
                .args(&["fff", "ggg"])
                // 環境變數設定
                // 目前底下是用 BTreeMap 來儲存的
                .env_clear()
                .envs({
                    use std::env;
                    use std::collections::HashMap;

                    env::vars().filter(|&(ref k, _)|
                        k == "TERM" || k == "TZ" || k == "LANG" || k == "PATH"
                    ).collect::<HashMap<String, String>>()
                })
                .envs({
                    use std::collections::HashMap;

                    [
                        ("MY_VAR1", "var1"),
                        ("MY_VAR2", "var2"),
                        ("MY_VAR3", "var3"),
                    ].iter()
                     .cloned()
                     .collect::<HashMap<&str, &str>>()
                })
                .env("MY_VAR1", "foo")
                .env("MY_VAR2", "bar")
                .env_remove("MY_VAR1")
                .env("MY_VAR1", "foo2")
                // 更改執行資料夾
                .current_dir("/tmp")
                // 更改 stdin/stdout/stderr
                .stdin(Stdio::null())
                .stdout(Stdio::piped())
                .stderr(Stdio::piped())
                // 在 Unix-like 平臺可以設定 user ID 和 group ID
                .uid(1000)
                .gid(10)
                // 執行並取得結果
                .output()
                .expect("command failed to execute");

    println!("{:?}", output.stdout);
    println!("{:?}", output.stderr);
    println!("{:?}", output.status);
    println!("---");


    ////////////////////
    // 執行方式二： .status()
    // 只想知道執行是否成功，不想取得執行輸出

    let status = Command::new("echo")
                         .arg("123")
                         .status()
                         .expect("command failed to execute");
    println!("{:?}", status);
    println!("---");


    ////////////////////
    // 執行方式三： .spawn()
    // 取得 child process 來做更多細部操作

    let mut child = Command::new("sleep")
                            .arg("2")
                            .spawn()
                            .expect("command failed to execute");
    println!("{:?}", child);

    // methods:
    // * child.wait()
    // * child.try_wait()
    // * child.wait_with_output()
    // * child.kill()
    match child.try_wait() {
        Ok(Some(status)) => println!("exited with: {}", status),
        Ok(None) => println!("command not ready yet"),
        Err(e) => println!("error attempting to wait: {}", e),
    }
    println!("---");



commands pipe
========================================

.. code-block:: rust

    // echo "0123456789" | grep -o "4567" | sed "s/56/65/"

    use std::process::{Command, Stdio};

    let child1 = Command::new("echo")
                         .arg("0123456789")
                         .stdout(Stdio::piped())
                         .spawn()
                         .expect("Failed to start echo process");

    let child2 = Command::new("grep")
                         .arg("-o")
                         .arg("4567")
                         .stdin(Stdio::from(child1.stdout.expect("failed to open stdout")))
                         .stdout(Stdio::piped())
                         .spawn()
                         .expect("Failed to start sed process");

    let result = Command::new("sed")
                         .arg("s/56/65/")
                         .stdin(Stdio::from(child2.stdout.expect("failed to open stdout")))
                         .stdout(Stdio::piped())
                         .output()
                         .expect("Failed to start sed process");

    println!("{:?}", result.status);
    println!("{:?}", String::from_utf8(result.stdout).unwrap());
    println!("{:?}", String::from_utf8(result.stderr).unwrap());




Rust std::process v.s. Python subprocess
========================================

* https://github.com/python/cpython/blob/master/Lib/subprocess.py



參考
========================================
