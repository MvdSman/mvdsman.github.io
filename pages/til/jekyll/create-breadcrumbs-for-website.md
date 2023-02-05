# Create breadcrumbs for website

## How To

Using Jekyll, we can dynamically get path info from the current page hierarchy.

1. Get tha page url and split it into crumbs
2. For each crumb, until the last, create a set of HTML links

### Start the breadcrumbs from the site's base URL

{% raw %}
```html
<div class="breadcrumbs" aria-label="breadcrumbs">
    <a href="{{ site.url }}{{ site.baseurl }}">{{ site.data.language.breadcrumb_start }}</a>
    {% assign crumbs = page.url | split: '/' %}
    {% for crumb in crumbs offset: 1 %}
        {% if forloop.last %}
            / <a class="current">{{ page.title }}</a>
        {% else %}
            / <a href="{{ site.url }}{{ site.baseurl }}{% assign crumb_limit = forloop.index | plus: 1 %}{% for crumb in crumbs limit: crumb_limit %}{{ crumb | append: '/' }}{% endfor %}">{{ crumb | replace:'-',' ' }}</a>
        {% endif %}
    {% endfor %}
</div>
```
{% endraw %}

## References

* [What are some good ways to implement breadcrumbs on a Jekyll site](http://stackoverflow.com/questions/9612235/what-are-some-good-ways-to-implement-breadcrumbs-on-a-jekyll-site)
* [Feeling Responsive - Jekyll theme](https://phlow.github.io/feeling-responsive/)
* https://jekyllcodex.org/without-plugin/breadcrumbs/#