icarus verilog
==============
verilog simulation tool

installation
------------
Main porting part - linux

| source code - git
| apt package - iverilog and gtkwave

ex::

    apt-get install iverilog
    apt-get install gtkwave

可參考官網: http://iverilog.icarus.com/

windows 也有包好的 installer(iverilog + gtkwave), 可參考: http://bleyer.org/icarus/

usage
----- 
| iverilog - 將 verilog source code 轉成 intermediate form (vvp assembly, 屬於 plain text)
| vvp - execute vvp assembly, 也可輸出 .vcd wave 檔
| gtkwave - 觀看 vcd 波形圖

iverilog 可以將 verilog 寫成的電路(source code)跟 testbench 一同編譯, 透過 vvp 執行後可輸出 testbench 的結果以及波型圖 .vcd, 可以再透過 gtkwave 觀察輸出的波型.

**compile**::

    iverilog -o $vvp_filename $all_source_file $testbench 

p.s. source code 跟 testbench 的順序不重要.

**execute**::
    
    vvp $vvp_filename

**about testbench source code**::

    $dumpfile("$waveform_filename") // 輸出的 waveform 檔名, gtkwave 只支援 .vcd 檔
    $dumpvars(0, $top_module_name_in_testbench);
    $finish // vvp program stop point (沒寫的話 vvp program 不會結束)

**waveform**::

    gtkwave simple.vcd

supplement
++++++++++
**example testbench**::

    module adder_tb;

        reg [3:0] in1;
        reg [3:0] in2;
        wire [4:0] out;

        initial begin
            $dumpfile("adder.vcd");
            $dumpvars(0, ad);
            $monitor("(in1, in2, out) = (%b, %b, %b)", in1, in2, out);

            in1 = 4'b0000;
            in2 = 4'b0000;
            # 10;
            in1 = 4'b1010;
            in2 = 4'b1101;
            # 10;
            in1 = 4'b0110;
            in2 = 4'b1001;
            # 10 $finish;
        end

        adder ad(  // ad is top module name in test bench
            .in1(in1),
            .in2(in2),
            .out(out)
        );

    endmodule

end
---
iverilog 跟一般 compiler 方式相似, 可以使用 makefile 輔助

可參考我計組程式的範例: https://github.com/u1240976/2013_CO_lab4to5/blob/master/makefile

ref
---
http://www.swarthmore.edu/NatSci/mzucker1/e15/iverilog-instructions.html

iverilog 官方 FAQ/wiki
