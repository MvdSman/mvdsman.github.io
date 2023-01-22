# Create automatic file index

## How To

To automatically create a list of files, use the following snippet.
- It replaces the markdown target to its generated HTML variant
- It uses the page title as link name
- It only lists files in the same directory as the current file

```
{% assign pages = site.pages | sort: 'title' %}

<ul>
    {% for item in pages %}
        {% assign html_item = item.name | replace: '.md', '.html' %}
        {% if item.dir == page.dir and item.path != page.path %}
           <li><a href="{{ html_item }}" > {{ item.title }} </a></li>
        {% endif %}
   {% endfor %}
</ul>
```

## References

- [Jekyll Talk - Directory Listing plugin help](https://talk.jekyllrb.com/t/directory-listing-plugin-help/5513/4)