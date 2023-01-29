# Create automatic file index

## How To

To automatically create a list of files, use the following snippet.
- It replaces the markdown target to its generated HTML variant
- It uses the page title as link name
- It only lists files in the same directory as the current file

### List all pages in the same directory

{% raw %}
```
{% assign pages = site.pages | sort: 'title' %}

<ul>
   {% for item in pages %}
      {% if item.dir == page.dir and item.path != page.path %}
         {% assign html_item = item.name | replace: '.md', '.html' %}
         <li><a href="{{ html_item }}" > {{ item.title }} </a></li>
      {% endif %}
   {% endfor %}
</ul>
```
{% endraw %}

### List all pages in a specific directory

{% raw %}
```
{% assign pages = site.pages | sort: 'title' %}

{% assign target_dir = page.dir | append: 'path/to/target_dir/' %}
<ul>
    {% for item in pages %}
        {% if item.dir == target_dir %}
            {% assign html_item = item.name | replace: '.md', '.html' %}
           <li><a href="{{ target_dir | append: html_item }}" > {{ item.title }} </a></li>
        {% endif %}
   {% endfor %}
</ul>
```
{% endraw %}

## References

- [Jekyll Talk - Directory Listing plugin help](https://talk.jekyllrb.com/t/directory-listing-plugin-help/5513/4)