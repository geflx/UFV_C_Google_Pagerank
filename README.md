# Google’s PageRank
First work in CS Course, implementing first algorithm used from Google to rank web searchs, the PageRank. In this problem, there are N pages, each one having at most N-1 linked output pages. You want to know which order to show the user in its search, based on its relevance. The iterative method for calculating the PageRank is implemented here, known as "Power Method".

## How to run?

First, make sure gcc and makefile are both installed in your machine.  
Secondly, make sure input file "input.txt" is in the same folder as "pagerank.c".  
Then, run this command in bash:
```
make
```
In case neither gcc or makefile are installed:
```
sudo apt-get install gcc
sudo apt-get install make
```
## Example

...
Consider the following instance, with five pages and its output liked pages:

<p align="center">
  <img src="assets/sample.png" align=center width=350 height=450/>
</p>

For each page, its PageRank value PR(i) is initialized as:

<p align="center">
  <img src="assets/init_pagerank.jpg" />
</p>

At each iteration k, PR(i) refreshs following this rule:

<p align="center">
  <img src="assets/pagerank.jpg" />
</p>

In the definition above:
• PR (i) denotes the PageRank of page i;  
• n is total number of pages;  
• d is a parameter, between 0 and 1. Normally, it is worth 0.85.  
• In (k) is the set of all pages that link to page k;  
• Out (k) is the set of all pages with a link coming out of page k;  
• |Y| denotes the number of elements in any set Y.  

The "Power Method" stops the calculation when E(k) < ε = 10-6 is achieved, begin E(k) described as follows: 
<p align="center">
  <img src="assets/stop_condition.jpg" />
</p>

...

## Conclusions
...

## Team
- Gabriel Félix
- Matheus Lima
