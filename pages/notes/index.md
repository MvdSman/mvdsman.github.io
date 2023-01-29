# Notes

<!-- Create automatic index of pages which can be found in this directory -->

{% assign pages = site.pages | sort: 'title' %}

<ul>
   {% for item in pages %}
      {% if item.dir == page.dir and item.path != page.path %}
         {% assign html_item = item.name | replace: '.md', '.html' %}
         <li><a href="{{ html_item }}" > {{ item.title }} </a></li>
      {% endif %}
   {% endfor %}
</ul>