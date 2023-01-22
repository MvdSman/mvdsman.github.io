# Notes

<!-- Create automatic index of pages which can be found in this directory -->

{% assign pages = site.pages | sort: 'title' %}

<ul>
    {% for item in pages %}
        {% assign html_item = item.name | replace: '.md', '.html' %}
        {% if item.dir == page.dir and item.path != page.path %}
           <li><a href="{{ html_item }}" > {{ item.title }} </a></li>
        {% endif %}
   {% endfor %}
</ul>