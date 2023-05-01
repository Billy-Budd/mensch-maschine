# [mensch-maschine](https://github.com/Billy-Budd/mensch-maschine/)
Code and projects from CS4375.004 Machine Learning course with Karen Mazidi. The document said to use underscores instead of spaces, but hyphens are more typical of the GitHub repositories that I've encountered, so I will be using hyphens. 

With the conclusion of the introduction to machine learning course, I can confidently say that I learned a lot about interpreting data and presenting that data in ways that can be used for this rapidly changing and growing field. While statistics and probabilities has never been my favorite topic, machine learning has allowed me to enjoy the subject much more; moreover, I finally feel like I get to do something with the knowledge I've gained rather than answer some math questions on a written test. In the future, I plan to make a model to better predict songs and artists that I would like since the normal mediums I have used (such as Spotify and YouTube recommendations) have become more and more lackluster. I have included a bit more of the soft skills and specifics about the technical skills in [this](autobahn.txt) file. Thanks for checking out this repository and I hope you find what you're looking for! 

Included in this repo is [Overview-of-ML](Overview-of-ML.pdf) which contains the answers to questions to the [Assignment: Portfolio Setup](/metropolis/assignment-portfolio-setup/portfolio-setup.pdf), including the instructions to create a [GitHub portfolio](/metropolis/Assignment-Portfolio-Setup/create-github-portfolio.pdf). Repositories are now in reverse order of assignment, instead of alphabetical order. This way the newest sub-repository is at the top (with the exception of [metropolis](/metropolis)).  

Name is in reference to the [Gesamtkunstwerk](https://www.theartstory.org/definition/gesamtkunstwerk/) of [Kraftwerk](https://en.wikipedia.org/wiki/Kraftwerk), an early-electronica German band, and their electronic music discography. [The Man-Machine or Die Mensch-Maschine](https://youtu.be/EPxGE1xWl_E?list=PLRp2a3r7tvpd3NpB_CwUbOoLxRgY4CwHh) is a [1978 electronic album](https://en.wikipedia.org/wiki/The_Man-Machine) that felt like an appropriate name and naming scheme for my projects in this machine learning course. 

## [metropolis](/metropolis)
Please click [here](metropolis.md) for the table of contents contained within it. Contains mainly loose files that pertain to various projects such as their assignment pages or pictures of their execution. 

Name is a reference to [Metropolis](https://youtu.be/SXTBGB2cKAk) in which is a reference to a the [Fritz Lang film](https://en.wikipedia.org/wiki/Metropolis_(1927_film)).

## [the-robots](/the-robots)
Program analyzes the data with kMeans, Hierarchical, and Model clustering and goes into detail about what those graphs mean. As I say in the file, the Rmd file needs additional libraries and I had to manually install some of those. Additionally, the program takes a long time for it to complete (about 10-20 minutes on my desktop with a recent cpu(AMD 5800X)). Of course, results will vary, but I recommend just looking at the pdf output. My file that comes from the notebook is part 3 which is why I have kept it out of order from the rest of the pdfs. 

- [data](/the-robots/perth.csv)
- [R-notebook](/the-robots/SAE-Part3.Rmd)
- [PDF-part3](/the-robots/SAE-Part3-JML190001-Team7.pdf)
- [PDF-part1](/the-robots/SAE-Part1-SureshMagan-Team7.pdf)
- [PDF-part2](/the-robots/SAE-Part2-RubenMathew-Team7.pdf)
- [PDF-part4](/the-robots/SAE-Part4-JaechulKim-Team7.pdf)
- [PDF-part5](/the-robots/SAE-Part5-JacobKatz-Team7.pdf)

The name for this is in reference to the song [The Robots](https://en.wikipedia.org/wiki/The_Robots) by Kraftwerk. You can listen to the song [here](https://youtu.be/68d8GRgiec4).

## [das-model](/das-model)
There are two programs [linreg](/das-model/das-model-linreg.cpp) and [naivebayes](/das-model/the-model-naivebayes.cpp) that perform analysis on the [titanic data set](/das-model/titanic_project.csv). Some pictures of the output are in the document [here](/das-model/CS4375-algorithms-from-scratch-response.pdf). 

- [PDF-response](/das-model/CS4375-algorithms-from-scratch-response.pdf)
- [dataset](/das-model/titanic_project.csv)
- [C++linreg](/das-model/das-model-linreg.cpp)
- [C++naivebayes](/das-model/the-model-naivebayes.cpp)
- [linreg-exe](/das-model/das-model-linreg.exe)
- [naivebayes-exe](/das-model/the-model-naivebayes.exe)

Name is in reference to the song [Das Model](https://en.wikipedia.org/wiki/Das_Model) by Kraftwerk. The song has an [English](https://youtu.be/KFq2pU21cNU) and a [German](https://youtu.be/qCFIRjycV5Q) version, and I chose to name each of the sources after one of each of the translations. 

## [blue-monday](/blue-monday)
The [data set](https://www.kaggle.com/datasets/jsphyg/weather-dataset-rattle-package) is a set of weather data for the country of Australia. It is also [here](/blue-monday/weatherAUS.csv). Both R programs use the data set to try and predict some aspect of Australia's weather. Regression attempts to predict pressure by using rainfall amounts, and classification attempts to predict whether it will rain tomorrow if it rained today. Both go into more detail which can be found in their .pdfs or in their source code. 

- [PDF-regression](/blue-monday/Regression.pdf)
- [PDF-classification](blue-monday/Classification.pdf)
- [R-notebook-regression](/blue-monday/Regression.rmd)
- [R-notebook-classification](/blue-monday/Classification.Rmd)

Name is in reference to the song [Blue Monday](https://youtu.be/c1GxjzHm5us) by [New Order](https://en.wikipedia.org/wiki/New_Order_(band)) which [samples](https://en.wikipedia.org/wiki/Blue_Monday_(New_Order_song)) the song [Uranium](https://youtu.be/t-QIWXiGuGw). While this is a bit of a stretch in the naming scheme, taking samples is important in data collection and statistics. I also really wanted to name something after Blue Monday. 

## [pocket-calculator](/pocket-calculator)
All of the main files can be found [here](/pocket-calculator), and all of the misc. files can be found in this [folder](/metropolis/portfolio-one-data-exploration) including assignment details. Program takes in data from Boston.csv and uses that data to find the sums, means, medians, and ranges of columns rm and medv. Program also determines correlation and covariance. 

- [source](/pocket-calculator/pocket-calculator.cpp)
- [formulas](/metropolis/portfolio-one-data-exploration/formulas.png) 
- execution images: [1](/metropolis/portfolio-one-data-exploration/pocket-calculator-1.PNG), [2](/metropolis/portfolio-one-data-exploration/pocket-calculator-2.PNG), and [3](/metropolis/portfolio-one-data-exploration/pocket-calculator-3.PNG)
- [R-notebook](/pocket-calculator/pocket-calculator-rstudio.pdf)
- [responses](/pocket-calculator/CS4375-data-exploration-response.pdf)
- [executable](/pocket-calculator/pocket-calculator.exe): [Boston.csv](/pocket-calculator/Boston.csv) must be in the same folder

Name is a reference to [Pocket Calculator](https://youtu.be/eSBybJGZoCU) which just seemed fitting because this was a program that was calculating some data. 

## [radioactivity](/radioactivity)
Data comes from kaggle, at this [link](https://www.kaggle.com/datasets/ayushnitb/song-features-dataset-regressing-popularity?resource=download).

- [R-notebook](/radioactivity/spotifyeval.rmd)
- [PDF](/radioactivity/spotifyeval.pdf)

Name is a reference to a [Radioactivity](https://youtu.be/fM2Ddrg1eFI), in which they relay some atomic-era fears and use tones to create morse code in eigth notes. It is also a pun, in which it emphasizes the radio activity like popular songs. 
