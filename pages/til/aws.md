<!-- Create automatic index of pages which can be found in a specific directory -->
{% assign pages = site.pages | sort: 'title' %}

## AWS

{% assign target_dir = page.dir | append: 'aws/' %}
<ul>
    {% for item in pages %}
        {% if item.dir == target_dir %}
            {% assign html_item = item.name | replace: '.md', '.html' %}
           <li><a href="{{ target_dir | append: html_item }}" > {{ item.title }} </a></li>
        {% endif %}
   {% endfor %}
</ul>