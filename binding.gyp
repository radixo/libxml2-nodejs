{
  "targets": [
    {
      "target_name": "libxml2",
      "sources": [
        "c14n.c",
	"encoding.c",
        "init.c",
	"IO.c",
	"parser.c",
	"tree.c",
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
