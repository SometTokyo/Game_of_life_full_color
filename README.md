## Game_of_life_full_color
> The Game of Life in 24-bit full color, written in C language. Project 1 from the Berkeley CS61Cfa20.

:maple_leaf: A photo of Conway, showing the effect under the 'life' rules, the inventor of the Game of Life.

![Conway](jc.gif)

Compile the program using the following command:  
使用以下指令编译程序：
```
$ make gameoflife
```

Place the image you wish to include in the iterations in the **testInput/** folder, making sure the file format is **.ppm**. Then run the following command:  
将您想参与迭代的图像放置在 **testInput/** 文件夹里，确保文件格式为 **.ppm**。接下来使用如下指令：
```
$ ./frames.csh [prefix of ppm file in testInputs] [rule in hex] [number of frames]
```

For example, by running the command below, you will get a 100-frame gif image under the life rules:  
例如通过执行下面的指令，您将得到一个在life规则下的100帧的gif图像：
```
$ ./frames.csh GliderGuns 0x1808 100
```

If you only want the result of one iteration, please run:  
如果您只想得到一次迭代结果，请执行：
```
$ ./gameOfLife [file] [rule]
```


[Regarding the rules](https://en.wikipedia.org/wiki/Life-like_cellular_automaton#A_selection_of_Life-like_rule)
