---
layout: page
subheadline: "Computational Molecular Biology"
title: "Sequence alignment [C++]"
teaser: "Basic sequence alignment in C++ using the Needleman and Wunsch-algorithm"
header:
    image_fullwidth: "header_R.jpg"
image:
    thumb:  needlemanwunsch.png
categories:
    - blog
tags:
    - Blog
    - C++
    - Computational Molecular Biology
    - Sequence Alignment
    - Multiple Sequence Alignment
comments: true
show_meta: true
---


## Introduction

Hello all, after some time I decided to create another post! My [last post](/blog/Poetry/) was about the analysis of 119 scraped poems, finding differences and similarities between different kinds of poems. This time, I will talk you through something more applicable to my own field of study: the basic alignment of two DNA sequences using the Needleman and Wunsch-algorithm. The reason I chose this subject is because it is my current subject on a course I'm following and I wanted to show what I am doing.
This is also the first time on this blog that I'll publish C++ code instead of R-script, as this was insisted on by my course supervisor. So please be aware that my code might not be the most optimal approach!

The Needleman and Wunsch-algorithm could be seen as one of the basic global alignment techniques: it aligns two sequences using a scoring matrix and a traceback matrix, which is based on the prior. Many other, way more complex algorithms have been written since the publication of this algorithm, but it is a good basis for more complicated problems and solutions.

*All data (anonymised if applicable), used script and created visualisations can be found in my [GitHub repository]({{ site.githublink }}).*

I love visualising interesting, uncommon datasets and working on projects so please [let me know](#disqus_thread) down in the comments if you have any request or interesting data laying around!

## Needleman and Wunsch-algorithm

I won't go into too much detail on how this algorithm works, but the basics will be covered along the way.
The principles are: a perfect match on a position on two sequences gives the highest score, mismatches get penalties and gaps are usually penalised using some function that takes into account how long the gap will actually be among multiple positions.

[![Figure not found!](/images/Cpp/2018-03-21_Needleman-Wunsch_pairwise_sequence_alignment.png "Needleman-Wunsch pairwise sequence alignment. By Slowkow - Own work, CC0, https://commons.wikimedia.org/w/index.php?curid=31963972.")](/images/Cpp/2018-03-21_Needleman-Wunsch_pairwise_sequence_alignment.png){:target="_blank"}


## 

The actual scoring of this is done using a small matrix in which all possible combinations are given a certain score:

|         |  C  |  T  |  A  |  G  |
|:-------:|:---:|:---:|:---:|:---:|
|  **C**  |  3  |  1  |  -3 |  -3 |
|  **T**  |  1  |  3  |  -3 |  -3 |
|  **A**  |  -3 |  -3 |  3  |  1  |
|  **G**  |  -3 |  -3 |  1  |  3  |

The reason for the 1 in A-G and C-T matching is because purine-purine (A/G) and pyrimidine-pyrimidine (C/T) mutations are biologically seen more common than other mutations.

The gap penalty will be calculated by the function ```gap_affinity()```, which defines an "affine gap penalty": the initial gap penalty will be higher with every directly following gap receiving a lower penalty. This ensures the algorithm to favor longer gaps over multiple singular gaps, which is also biologically seen more realistic.

<details>
  <summary class="summary">Toggle C++ code</summary>
  <div markdown="1">
```cpp
int gap_affinity (int gap, int gap_ext, int& length){
    int gap_aff = gap + (gap_ext * length);

    return gap_aff;
}
```
  </div>
</details>

