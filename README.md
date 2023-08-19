## Game-of-life-full-color
The Game of Life in 24-bit full color, written in C language. Project 1 from the Berkeley CS61Cfa20.

![Conway](jc.gif)

Compile the program using the following command:  
使用以下指令编译程序：
```
$ make gameoflife
```

Place the image you wish to include in the iterations in the testInput/ folder, making sure the file format is .ppm. Then use the following command:  
将您想参与迭代的图像放置在testInput/文件夹里，确保文件格式为.ppm。接下来使用如下指令：
```
$ ./frames.csh [prefix of ppm file in testInputs] [rule in hex] [number of frames]
```

For example, by executing the command below, you will get a 100-frame gif image under the life rules:  
例如通过执行下面的指令，您将得到一个在life规则下的100帧的gif图像：
```
$ ./frames.csh GliderGuns 0x1808 100
```

If you only want the result of one iteration, please execute:  
如果您只想得到一次迭代结果，请执行：
```
$ ./gameOfLife [file] [rule]
```
Note, the output result is in .ppm format and the output path is studentOutputs/  
注意，输出结果为.ppm输出路径为studentOutputs/

[Regarding the rules](https://en.wikipedia.org/wiki/Lifelike_cellular_automaton#A_selection_of_Life-like_rules)
