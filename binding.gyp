{
  "targets": [
    {
      "target_name": "libxml2",
      "sources": [
        "init.c",
	"parser.c",
        "c14n.c",
	"xpath.c"
      ],
      "include_dirs": [
        "<!(pkg-config --cflags-only-I libxml-2.0 | sed s/-I//g)"
      ],
      "link_settings": {
        "libraries": [
          "<!@(pkg-config --libs-only-l libxml-2.0)"
        ]
      }
    }
  ]
}
