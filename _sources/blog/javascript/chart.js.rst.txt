:title: Chart.js 簡單的畫出 Chart
:slug: chart-js
:date: 2014-02-22 14:06
:category: Misc
:tags: Javascript
:author: wdv4758h
:summary: 最近剛好碰到要畫 Chart，所以嘗試了 Chart.js，順便做一下紀錄

.. raw:: html

    <script src="//cdnjs.cloudflare.com/ajax/libs/Chart.js/0.2.0/Chart.min.js"></script>

`Chart.js <http://www.chartjs.org/>`_ 是利用 HTML5 的 canvas 去畫的，
而 Chart.js 這個 library 本身是 open source 的 (MIT license) (`Chart.js - github <https://github.com/nnnick/Chart.js>`_)

所以到底要怎麼用呢？

其實要用這個 library 很簡單，
首先要先把 Chart.js (或 Chart.min.js) include 進來 (這邊先用 CDN 上的做範例，要擺到自己機器上的再去修改 src)

.. code-block:: html

    <script src="//cdnjs.cloudflare.com/ajax/libs/Chart.js/0.2.0/Chart.min.js"></script>

再來是要有畫布啦 ~

.. code-block:: html

    <canvas id="myChart" width="400" height="400"></canvas>

接著是給資料然後畫圖 ~

.. code-block:: javascript

    var data = [
        {
            value: 30,
            color:"#F38630"
        },
        {
            value : 50,
            color : "#E0E4CC"
        },
        {
            value : 100,
            color : "#69D2E7"
        }
    ];
    //Get the context of the canvas element we want to select
    var ctx = document.getElementById("myChart").getContext("2d");
    var myNewChart = new Chart(ctx).Pie(data);

.. raw:: html

    <canvas id="myChart" width="400" height="400"></canvas>
    <script>
        var data = [
            {
                value: 30,
                color:"#F38630"
            },
            {
                value : 50,
                color : "#E0E4CC"
            },
            {
                value : 100,
                color : "#69D2E7"
            }
        ];
        var ctx = document.getElementById("myChart").getContext("2d");
        var myNewChart = new Chart(ctx).Pie(data);
    </script>

Chart.js 目前有六種 Charts，
可以在 `官方文件 <http://www.chartjs.org/docs/>`_ 看到相關的設定、資料格式，
每個 Chart 除了本身的資料外，還有一些 option 可以調整，
例如要不要 animation 啦、要不要顯示 label 啦 ... etc

六種 Chart
========================================

Line Chart
------------------------------

.. raw:: html

    <canvas id="LineChart" width="800" height="400"></canvas>
    <script>
    var data = {
        labels : ["January","February","March","April","May","June","July"],
        datasets : [
            {
                fillColor : "rgba(220,220,220,0.5)",
                strokeColor : "rgba(220,220,220,1)",
                pointColor : "rgba(220,220,220,1)",
                pointStrokeColor : "#fff",
                data : [65,59,90,81,56,55,40]
            },
            {
                fillColor : "rgba(151,187,205,0.5)",
                strokeColor : "rgba(151,187,205,1)",
                pointColor : "rgba(151,187,205,1)",
                pointStrokeColor : "#fff",
                data : [28,48,40,19,96,27,100]
            }
        ]
    };
    var ctx = document.getElementById("LineChart").getContext("2d");
    new Chart(ctx).Line(data);
    </script>

Bar Chart
------------------------------

.. raw:: html

    <canvas id="BarChart" width="800" height="400"></canvas>
    <script>
    var data = {
        labels : ["January","February","March","April","May","June","July"],
        datasets : [
            {
                fillColor : "rgba(220,220,220,0.5)",
                strokeColor : "rgba(220,220,220,1)",
                data : [65,59,90,81,56,55,40]
            },
            {
                fillColor : "rgba(151,187,205,0.5)",
                strokeColor : "rgba(151,187,205,1)",
                data : [28,48,40,19,96,27,100]
            }
        ]
    };
    var ctx = document.getElementById("BarChart").getContext("2d");
    new Chart(ctx).Bar(data);
    </script>

Radar chart
----------------------------------------

.. raw:: html

    <canvas id="RadarChart" width="800" height="400"></canvas>
    <script>
    var data = {
        labels : ["Eating","Drinking","Sleeping","Designing","Coding","Partying","Running"],
        datasets : [
            {
                fillColor : "rgba(220,220,220,0.5)",
                strokeColor : "rgba(220,220,220,1)",
                pointColor : "rgba(220,220,220,1)",
                pointStrokeColor : "#fff",
                data : [65,59,90,81,56,55,40]
            },
            {
                fillColor : "rgba(151,187,205,0.5)",
                strokeColor : "rgba(151,187,205,1)",
                pointColor : "rgba(151,187,205,1)",
                pointStrokeColor : "#fff",
                data : [28,48,40,19,96,27,100]
            }
        ]
    };
    var ctx = document.getElementById("RadarChart").getContext("2d");
    new Chart(ctx).Radar(data);
    </script>

Polar area chart
------------------------------

.. raw:: html

    <canvas id="PolarChart" width="800" height="400"></canvas>
    <script>
    var data = [
        {
            value : 30,
            color: "#D97041"
        },
        {
            value : 90,
            color: "#C7604C"
        },
        {
            value : 24,
            color: "#21323D"
        },
        {
            value : 58,
            color: "#9D9B7F"
        },
        {
            value : 82,
            color: "#7D4F6D"
        },
        {
            value : 8,
            color: "#584A5E"
        }
    ];
    var ctx = document.getElementById("PolarChart").getContext("2d");
    new Chart(ctx).PolarArea(data);
    </script>

Pie chart
------------------------------

.. raw:: html

    <canvas id="PieChart" width="800" height="400"></canvas>
    <script>
    var data = [
        {
            value: 30,
            color:"#F38630"
        },
        {
            value : 50,
            color : "#E0E4CC"
        },
        {
            value : 100,
            color : "#69D2E7"
        }
    ];
    var ctx = document.getElementById("PieChart").getContext("2d");
    new Chart(ctx).Pie(data);
    </script>

Doughnut chart
------------------------------

.. raw:: html

    <canvas id="DoughnutChart" width="800" height="400"></canvas>
    <script>
    var data = [
        {
            value: 30,
            color:"#F7464A"
        },
        {
            value : 50,
            color : "#E2EAE9"
        },
        {
            value : 100,
            color : "#D4CCC5"
        },
        {
            value : 40,
            color : "#949FB1"
        },
        {
            value : 120,
            color : "#4D5360"
        }

    ];
    var ctx = document.getElementById("DoughnutChart").getContext("2d");
    new Chart(ctx).Doughnut(data);
    </script>

Ref
========================================

- `Chart.js <http://www.chartjs.org/>`_
