========
VBScript
========
* 以下 VBScript 用來把 ``src.pptx`` 的每一頁投影片都輸出到 ``exported-pictures/`` 裡面

  ::

    pwd = CreateObject("Scripting.FileSystemObject").GetParentFolderName(WScript.ScriptFullName)
    src_filename = "src.pptx"
    target_folder = "exported-pictures/"

    Set PowerPointApp = CreateObject("PowerPoint.Application")
    Set PresentationObj = PowerPointApp.Presentations.Open(pwd & "\" & src_filename, False, False, False)
    For Each slide In PresentationObj.Slides
        ' MsgBox slide.SlideIndex
        slide.Export pwd & "\" & target_folder & slide.SlideIndex & ".png", "PNG"
    Next
    MsgBox "Done, total " & PresentationObj.Slides.Count & " pages"
    PowerPointApp.Quit

  - 以下 VBScript 可以輸入範圍，以空白字元分隔，空字串為全部頁面（未做防呆） ::

      pwd = CreateObject("Scripting.FileSystemObject").GetParentFolderName(WScript.ScriptFullName)
      src_filename = "src.pptx"
      target_folder = "exported-pictures/"

      Set PowerPointApp = CreateObject("PowerPoint.Application")
      Set PresentationObj = PowerPointApp.Presentations.Open(pwd & "\" & src_filename, False, False, False)

      indices = Split(InputBox("Input the range you want to export to png, split numbers with space, empty for all pages."))

      if UBound(indices) = -1 Then
          ReDim indices(PresentationObj.Slides.Count - 1)
          For index=0 to UBound(indices)
              indices(index) = index + 1
          Next
      End if

      For Each index In indices
          PresentationObj.Slides(CInt(index)).Export pwd & "\" & target_folder & index & ".png", "PNG"
      Next
      MsgBox "Done, total " & (UBound(indices) + 1) & " pages"
