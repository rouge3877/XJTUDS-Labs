# 实验13：迷宫问题

## 题目描述

迷宫实验是取自心理学的一个古典实验。在该实验中，把一只老鼠从一个无顶大盒子的门放入，在盒中设置了许多墙，对行进方向形成了多处阻挡。盒子仅有一个出口，在出口处放置一块奶酪，吸引老鼠在迷宫中寻找道路以到达出口。对同一只老鼠重复进行上述实验，一直到老鼠从入口到出口，而不走错一步。老鼠经多次试验终于得到它学习走迷宫的路线。

迷宫由m行n列的二维数组设置，0表示无障碍，1表示有障碍。设入口为（1，1），出口为（m，n），每次只能从一个无障碍单元移到周围四个方向上任一无障碍单元。编程实现对任意设定的迷宫，求出一条从入口到出口的通路，或得出没有通路的结论。

## 解题思路

1. **生成迷宫：**
   - 使用`generate_maze`函数生成一个迷宫，迷宫是一个二维数组，其中每个元素表示一个单元格，包含四个方向的墙和一个标志位表示是否已经访问过。
   - 通过随机选择单元格，使用深度优先搜索（DFS）算法生成迷宫路径，并打开路径两侧的墙。迷宫路径生成的具体步骤在注释中有详细解释。
   - 起点和终点分别在迷宫的左上角和右下角，将它们的墙打开。
2. **绘制迷宫：**
   - 使用`display_maze`函数将迷宫以图像形式显示。
   - 每个单元格用一个方块表示，单元格内部填充，墙部分用像素表示。
   - 外墙加粗，入口和出口打开，起点和终点标记。
3. **BFS寻找路径：**
   - 使用`find_path`函数利用广度优先搜索（BFS）算法在生成的迷宫中寻找从起点到终点的路径。
   - 使用一个队列存储待访问的单元格，并记录每个单元格的前一个单元格，从而构建路径。
4. **显示迷宫和路径：**
   - 使用`display_maze_solve`函数在显示的图像上标记出找到的路径。
   - 如果找不到路径，则打印提示信息。
5. **命令行参数处理：**
   - 使用`sys.argv`处理命令行参数，接受两个正整数作为行和列的尺寸。
   - 如果没有提供参数，默认生成一个10x10的迷宫。
6. **主函数：**
   - 在`main`函数中调用上述函数，生成迷宫、显示迷宫、寻找路径，并将结果以图像形式展示。
   - 如果提供了命令行参数，则使用指定的行和列尺寸生成迷宫。

## 大致的算法

### 迷宫的生成

迷宫生成算法的部分主要使用了深度优先搜索（DFS）的思想。下面对代码中的关键部分进行详尽的说明：

1. `generate_maze` 函数的目标是生成一个迷宫，其中 `maze_total_rows` 和 `maze_total_cols` 分别表示迷宫的总行数和总列数。
2. `message_of_point` 是一个三维数组，用于保存每个迷宫单元格的信息。其形状是 `(maze_total_rows, maze_total_cols, 5)`，其中：
   - 第一个维度表示行数。
   - 第二个维度表示列数。
   - 第三个维度有五个元素，分别表示当前单元格的左、上、右、下是否有墙以及该单元格是否已被访问。
3. 迷宫生成的主要过程：
   - 初始位置为 `(0, 0)`，将其添加到 `history_found` 中。
   - 在 `while` 循环中，不断从 `history_found` 中随机选择一个单元格 `(this_row, this_col)`。
   - 将选择的单元格标记为已访问 (`message_of_point[this_row, this_col, 4] = 1`)。
   - 检查当前单元格四个方向，如果相邻的单元格未被访问，将其添加到 `history_found` 中，并在当前单元格和相邻单元格之间打通路径（打通墙）。
   - 迭代直到 `history_found` 为空，即无法再继续探索时，生成的迷宫就是一个完整的迷宫。
4. 关键变量和操作：
   - `history_found` 是一个存储已访问位置的堆栈，用于深度优先搜索。
   - `check` 存储当前单元格中有相邻未访问单元格的方向。
   - `move_direction` 随机选择一个方向。
   - `message_of_point` 用于记录每个单元格的信息，包括墙和是否已访问。
5. 最终，迷宫生成算法保证了每个单元格都可达，并且通过深度优先搜索的方式生成了一条路径，形成了一个随机生成的迷宫。

### 迷宫寻路部分

这段代码包含了一个基于广度优先搜索（BFS）的迷宫寻路算法。下面详细解释关键部分：

1. **find_path 函数**:
   - `maze`: 生成的迷宫，其中包含了每个单元格的信息，包括墙的位置。
   - `start`: 起点的坐标 `(row, col)`。
   - `end`: 终点的坐标 `(row, col)`。
2. **message_of_point 数组**:
   - `message_of_point` 是一个与迷宫数组结构相同的数组，用于存储每个单元格的信息，包括墙的位置和访问状态。
   - 初始化时，将 `message_of_point[:, :, :4]` 的值设置为迷宫的信息，即墙的位置。
   - 第五个维度 `message_of_point[:, :, 4]` 用于标记单元格是否已经在搜索中被访问，初始值为0。
3. **BFS 寻路算法**:
   - 使用队列 `queue` 存储待访问的单元格坐标，初始时将起点 `start` 加入队列。
   - 使用字典 `previous_point` 存储每个单元格的前驱，以便在找到终点后回溯路径。
   - 在每次循环中，从队列中取出一个单元格`(this_row, this_col)`进行如下判断：
     - 如果左边的单元格未访问且有通路，则将其加入队列，并标记为已访问。
     - 如果上方的单元格未访问且有通路，则将其加入队列，并标记为已访问。
     - 如果右边的单元格未访问且有通路，则将其加入队列，并标记为已访问。
     - 如果下方的单元格未访问且有通路，则将其加入队列，并标记为已访问。
     - 如果当前单元格是终点，停止搜索。
4. **回溯路径**:
   - 从终点开始，通过 `previous_point` 字典回溯到起点，得到路径上的每个单元格坐标。
   - 将路径逆序插入 `path` 列表中。
5. **display_maze_solve 函数**:
   - 该函数根据找到的路径，将路径上的单元格在迷宫图像上标记为通路，以突显路径。
6. **main 函数**:
   - 读取用户输入的行列数，生成迷宫，显示原始迷宫图像。
   - 寻找路径，如果找到则显示带有路径的迷宫图像。

总体而言，这一部分通过广度优先搜索算法在生成的迷宫中找到起点到终点的路径，并通过图像展示了迷宫和找到的路径。算法保证了找到的路径是最短路径。

## 输入输出

### 输入输出处理

让我们分析输入输出的处理：

#### 输入处理

命令行参数（sys.argv）：

- 如果命令行参数的数量既不是2个也不是0个，就会输出错误信息并调用`help()`函数。
- 如果参数数量是0个，则使用默认的迷宫尺寸（10x10）。
- 如果参数数量是2个，会尝试将它们解析为整数，如果无法解析或者解析结果不是正整数，同样输出错误信息并调用`help()`函数。

#### 输出处理

1. **生成迷宫输出：**`generate_maze` 函数会返回一个三维数组 `message_of_point` 表示迷宫的结构，其中包含每个单元格四面的墙以及是否被访问过。输出时通过 `print(message_of_point)` 打印生成的迷宫信息。
2. **绘制迷宫输出：**`display_maze` 函数通过Matplotlib库生成迷宫的可视化图像，其中墙用二进制表示。输出时使用 `plt.imshow` 函数显示图像。
3. **找到路径输出：**`find_path` 函数通过BFS算法寻找迷宫中的路径，返回路径的坐标。如果找到路径，会打印路径的坐标。
4. **迷宫求解显示输出：**`display_maze_solve` 函数通过将找到的路径在图像上标记为不同的颜色来展示求解的迷宫。输出时使用 `plt.imshow` 函数显示带有路径的图像。
5. **主程序输出：**主程序通过调用上述函数，并使用Matplotlib库展示生成的迷宫和找到的路径。

### 输入输出样例

#### 输入输出样例1

```python
# 以默认大小运行（10x10）
python3 maze.py
```

![maze.png](.\maze1010.png)

#### 输入输出样例2

```python
python3 maze.py 40 30
```

![70236296190](.\maze4030.png)

#### 输入输出样例3

```yaml
rouqi@ROUGE-LAPTOP-LEGION:~/python-repo$ python3 maze.py --help
Usage: python3 maze.py <num_rows> <num_cols>
       <num_rows> and <num_cols> must be positive integers,
       and <num_rows> * <num_cols> must be greater than 1.
       If no arguments are provided, the default maze size is 10x10.
```

## 总结

### 算法复杂度分析

#### 生成迷宫算法 `generate_maze`

- **时间复杂度：**主要由 while 循环控制，每次循环中的操作都是常数时间的。最坏情况下，每个单元格都会被访问一次，所以总的时间复杂度为 **O(maze_total_rows * maze_total_cols)**，其中 `maze_total_rows` 为行数，`maze_total_cols` 为列数。
- **空间复杂度：**使用了大小为**O(maze_total_rows * maze_total_cols * 5)** 的三维数组 `message_of_point` 来保存每个单元格的信息。所以总的空间复杂度为 **O(maze_total_rows * maze_total_cols)**。

#### 绘制迷宫算法 `display_maze`

- **时间复杂度：**主要由两个嵌套的循环控制，嵌套循环的次数与迷宫的大小成正比。所以总的时间复杂度为 **O(maze_total_rows * maze_total_cols)**。
- **空间复杂度：**使用了大小为 **O(rows_num * cols_num * 10 * 10)** 的二维数组 `image_output` 来保存图像信息。所以总的空间复杂度为 **O(rows_num * cols_num)**。

#### 使用BFS算法寻找路径 `find_path`

- **时间复杂度：**BFS算法的时间复杂度是**O(V + E)**，其中 V 为顶点数，E 为边数。在这里，V为迷宫的单元格数，E为边的数量（每个单元格四个方向的边），时间复杂度**O(maze_total_rows * maze_total_cols)**。
- **空间复杂度：**
  - 使用了大小为 **O(maze_total_rows * maze_total_cols * 5)** 的三维数组 `message_of_point` 来保存每个单元格的信息。
  - 使用了大小为 **O(maze_total_rows * maze_total_cols)** 的字典 `previous_point` 用于存储路径。
  - 所以总的空间复杂度**O(maze_total_rows * maze_total_cols)**。

### 改进空间

1. **减少历史记录的选择操作**：
   - 当随机选择的单元格已经被访问过，可以避免将其添加到历史记录中，而是直接选择下一个单元格。这样可以减少历史记录的大小，提高生成迷宫的效率。
2. **迭代生成算法**：
   - 可以考虑使用迭代生成算法，如Prim's算法或Kruskal's算法，来替代当前的生成迷宫算法。这些算法在某些情况下可能比随机生成迷宫更高效。
3. **BFS算法优化**：
   - 在BFS算法中，可以尝试优化数据结构的选择，例如使用队列来代替列表，以提高查找和弹出元素的效率。
4. **图像显示优化**：
   - 在图像显示部分，可以考虑使用更高效的图像生成方法，例如直接使用matplotlib的imshow方法来绘制墙和路径，而不是使用循环逐个设置像素值。

--------------
