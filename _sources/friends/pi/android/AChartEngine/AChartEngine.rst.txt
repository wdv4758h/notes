=================
AChartEngine 筆記
=================

概念
----

使用 AChartEngine 的步驟

1.  準備好要顯示的資料 ::

      int[] y1 = {5, 10, 2};

2.  把資料放入 Series 中 ::

      XYSeries y1_series = new XYSeries("test");
      y1_series.add(0, y[0]);
      y1_series.add(1, y[1]);
      y1_series.add(2, y[2]);

3.  把 Series 放入 Dataset 中 ::

      XYMultipleSeriesDataset my_dataset = new XYMultipleSeriesDataset();
      my_dataset.addSeries(y1_series);

    + 若有不同群的資料需在同一張圖中顯示，放在不同 Series 中，都加入同一個 Dataset

4.  準備好每份 Series 所需的 Renderer ::

      XYSeriesRenderer y1_renderer = new XYSeriesRenderer();
      y1_renderer.setColor(...);
      ...

5.  把各 Renderer 加入圖表的 Renderer ::

      XYMultipleSeriesRenderer multiRenderer = new XYMultipleSeriesRenderer();
      multiRenderer.addSeriesRenderer(y1_renderer);

5.  透過 ChartFactory 取得圖表 view ::

      GraphicalView barchart_view;
      barchart_view = ChartFactory.getBarChartView(this, dataset, multiRenderer, BarChart.Type.DEFAULT);

6.  把圖表 view 動態加入 layout 中 ::

      LinearLayout wrapperview = (LinearLayout)findViewById(R.id.graphical_view_wrapper);
      wrapperview.addView(barchart_view);

7.  動態增加資料 ::

      y1_series.add(3, 50);
      barchart_view.repaint();

其他
----

- 設定 chart view 的 Layout 大小

  - chart view 預設大小都是 match_parent，不設定大小的話會佔滿所有空間

  1.  設定 layout paramaters::

        graphActivityLayout.addView(mChart，1);
        LinearLayout.LayoutParams layoutParams = (LinearLayout.LayoutParams) mChart.getLayoutParams();
        layoutParams.

  2.  包一層 view，固定外面的 view 大小

      - worked

- 設定 chart view 的顯示範圍 ::

    XYMultipleSeriesRenderer mRenderer;
    mRenderer.setXAxisMin(minX);
    mRenderer.setXAxisMax(maxX);
    mChartView.repaint();

- 設定 chart 的背景色 ::

    XYMultipleSeriesRenderer mRenderer;
    mRenderer.setApplyBackgroundColor(true);
    mRenderer.setBackgroundColor(Color.RED);
    mRenderer.setMarginsColor(Color.RED);

- 設定座標軸的顏色 ::

    XYMultipleSeriesRenderer mRenderer;
    mRenderer.setYLabelsColor(0, Color.BLACK);  // 依 renderer 數量及順序而定

- 其他 ::

    renderer.setShowGrid(true);
