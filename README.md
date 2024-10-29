<h1>An Analysis on Efficient Convolution Compiler Techniques</h1>
CS Seminar Research with Dr. Megan Thomas @ Cal State Stanislaus | Aug. - Dec. 2023<br><br>

**Abstract:**<br>
This paper will first provide a brief background in data center machine idling, the proportional power usage (computationally intensive processes will proportionally consume the same percentage of power) of machine learning computations in data centers (Weihl et al., 2011), and the effectiveness of loop tiling methods in reducing power consumption (Ni et al., 2018). Furthermore, this paper will discuss the simple algorithmic logic behind loop tiling (Kelefouras et al., 2022), its memory optimization in multidimensional matrices, and the variables (ie: tile size selection (Zhao et al., 2018) and layer padding size (Alwani et al., 2016)) that enable it to perform successfully. Lastly, this paper will discuss the research done by Yuanhui Ni et al. (2018) assessing the effectiveness of integrating loop tiling in specialized neuromorphic hardware; examining their initial observation of RRAM (Resistive Random-Access Memory, hardware using resistance as a measure for binary representation) crossbar (architecture in RRAM for efficient computations) based CNN, experimental setup, and data evaluation.<br>


<h2>Performance Metrics Images</h2>

Tile Size: 32 x 32

<img src='https://github.com/yammei/CNN_TILING/blob/main/testdata/tileSize32/graph32.png' alt=''>

Tile Size: 64 x 64

<img src='https://github.com/yammei/CNN_TILING/blob/main/testdata/tileSize64/graph64.png' alt=''>

Tile Size: 84 x 84

<img src='https://github.com/yammei/CNN_TILING/blob/main/testdata/tileSize84/graph84.png' alt=''>

Tile Size: 128 x 128

<img src='https://github.com/yammei/CNN_TILING/blob/main/testdata/tileSize128/graph128.png' alt=''>

Tile Size: 224 x 224

<img src='https://github.com/yammei/CNN_TILING/blob/main/testdata/tileSize224/graph224.png' alt=''>

Tile Size: 128 x 128

<img src='https://github.com/yammei/CNN_TILING/blob/main/testdata/tileSize128/graph128.png' alt=''>

Tile Size: 256 x 256

<img src='https://github.com/yammei/CNN_TILING/blob/main/testdata/tileSize256/graph256.png' alt=''>

Tile Size: 512 x 512

<img src='https://github.com/yammei/CNN_TILING/blob/main/testdata/tileSize512/graph512.png' alt=''>
