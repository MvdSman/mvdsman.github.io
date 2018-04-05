---
layout: page
subheadline: "DataViz Request"
title: "Working Hours [R]"
teaser: "Reddit request for visualisation of a dataset concerning cleaning times of hotel rooms."
header:
    image_fullwidth: "header_R.jpg"
image:
    thumb:  reddit.png
categories:
    - blog
tags:
    - Blog
    - R
    - Visualisation
    - Reddit
comments: true
show_meta: true
---

Welcome to my first post posted on this site! This will be quite a short one, but I hope it will be the first of many.

*All data (anonymised if applicable), used script and created visualisations can be found in my [GitHub repository]({{ site.githublink }}).*

I love visualising interesting, uncommon datasets so please [let me know](#disqus_thread) down in the comments if you have any interesting data laying around!

Let's just skip towards the code now, shall we?

The used dataset is acquired from [this Reddit post](https://www.reddit.com/r/DataVizRequests/comments/7jqso6/request_i_would_like_to_have_some_simple_graphs/) on DataViz Requests. I edited the dataset to make it more appropriate for R. For more information on the data, please read the post.

Of course, the libraries have to be loaded in R. Below is the most common set of libraries I use for almost all scripts I write. Note that I also add the line `theme_set(theme_bw())` to my setup code. This will simply set the plotting theme to a simple black and white, which is preferred for more official situations like publications or theses as described in this request.

```r
library(knitr)
library(dplyr)
library(tidyr)
library(data.table)
library(ggplot2)
library(corrgram)
theme_set(theme_bw())
```

When loading the datasets, I tend to use `read.csv()` for files smaller than 1MB and `read_csv()` for the larger files. I immediately created some extra variables for the plots I planned to create. I arranged on Distance for when I want to look at the data itself. For a clear indication of what variables are added during the R-script, I like to distinguish them with the use of either the dot and the underscore.

```r
data <- as.data.frame(read.csv("WorkingHours.csv"))
data$Room <- as.factor(data$Room)
data <- data %>% group_by(Room, Cleaning.type) %>% mutate(Mean_room=mean(Minutes), Mean_SD=sd(Minutes)) %>% group_by(Cleaning.type) %>% mutate(Mean_Type=mean(Minutes)) %>% arrange(Distance)
```

**Head of the dataset:**

|  Room  |  Distance  |  Seconds.from.service  |  Cleaning.type  |  Minutes  |  Mean_room  |  Mean_SD  |  Mean_Type  |
|:------:|:----------:|:----------------------:|:---------------:|:---------:|:-----------:|:---------:|:-----------:|
|  208   |    7.5     |          3.75          |    Checkout     |    65     |   47.375    | 10.61572  |  52.01587   |
|  208   |    7.5     |          3.75          |    Checkout     |    59     |   47.375    | 10.61572  |  52.01587   |
|  208   |    7.5     |          3.75          |    Checkout     |    40     |   47.375    | 10.61572  |  52.01587   |
|  208   |    7.5     |          3.75          |    Checkout     |    60     |   47.375    | 10.61572  |  52.01587   |
|  208   |    7.5     |          3.75          |    Checkout     |    55     |   47.375    | 10.61572  |  52.01587   |
|  208   |    7.5     |          3.75          |    Checkout     |    49     |   47.375    | 10.61572  |  52.01587   |

After this, it's time to visualise! Let's begin with creating some boxplots to get a general idea of the data...

```r
ggplot(data, aes(x=Room, y=Minutes)) +
  geom_boxplot() +
  facet_wrap(~Cleaning.type) +
  ggtitle("Time taken to clean a room","Facetted by the type of clean-up")
```

![Time taken to clean a room. Facetted by type of clean-up.]({{ site.urlimg }}R/2017-12-14_Rplot1.jpeg "Boxplot 1")

This plot shows a clear difference between the time needed to clean a room upon checkout compared to the time needed for a stay-over. The rooms themselves don't really differ that much from each other.

```r
ggplot(data, aes(x=Cleaning.type, y=Minutes)) +
  geom_boxplot() +
  ggtitle("Time taken for both types of clean-up")
```

![Time taken for both types of clean-up.]({{ site.urlimg }}R/2017-12-14_Rplot2.jpeg "Boxplot 2")

When looking at the variable *Cleaning.type*, a clear difference between the two types can be seen. This supports the claims from the first boxplot.

Next, we will look at how *Distance* might be involved in the amount of time it took to clean a room. For this, a jitterplot will be created in combination with some lines connecting the means.

```r
ggplot(data, aes(x=Distance, y=Minutes, group=Cleaning.type, shape=Cleaning.type)) +
  geom_jitter() +
  geom_line(aes(y=Mean_room, linetype=Cleaning.type)) +
  scale_shape_manual(values=c(3,1)) +
  ggtitle("Time taken to clean a room","Grouped by the type of clean-up")
```

![Time taken to clean a room.]({{ site.urlimg }}R/2017-12-14_Rplot3.jpeg "Jitterplot")

This plot shows the same difference in *Cleaning.type* as the boxplots, but in a better sense of dimensionality using the actual distance to a room instead of just the room number. Because the amount of datapoints might not always be as helpful as a cleaner lineplot with error bars, we'll create one of those too!

```r
ggplot(data, aes(x=Distance, y=Minutes, group=Cleaning.type)) +
  geom_line(aes(y=Mean_room, linetype=Cleaning.type)) +
  geom_errorbar(aes(ymin=Mean_room-Mean_SD, ymax=Mean_room+Mean_SD)) +
  ggtitle("Time taken to clean a room","Grouped by the type of clean-up")
```

![Time taken to clean a room.]({{ site.urlimg }}R/2017-12-14_Rplot4.jpeg "Lineplot")

The errorbars (&#177;1SD) were chosen for a cleaner plot. This plot suggests a clear difference between the two cleaning types. The distance does not, however, show any significant differences in the time measured other than an increase in variance for the longer distances.

To say something about the significance of the observations, statistics are obviously required. This time I will not cover that part because I am somewhat limited in time this period.
I will, however, show a quick correlation table to see how the variables relate to each other.

```r
corrgram(data, order=FALSE, lower.panel=panel.conf, upper.panel=panel.pts,
         diag.panel=panel.density, main="Correlation matrix")
```

![Correlation table of the dataset.]({{ site.urlimg }}R/2017-12-14_Rplot5.jpeg "Corrgram")

The correlation table shows that the average cleaning time per room per type (*Mean_room*) is highly correlated with the average cleaning time per type (*Mean_Type*), indicating that the distance does not influence the cleaning time for a certain type. The low correlation of *Distance* with *Minutes* shows no relation between these two variables: the cleaning time is not influenced by the distance of a room.
