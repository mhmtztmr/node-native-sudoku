{
  "targets": [
   {
     "include_dirs" : [
        "<!(node -e \"require('nan')\")"
      ],
      "target_name": "sudoku",
      "sources": [ "main.cpp" ]
    }
  ]
}
