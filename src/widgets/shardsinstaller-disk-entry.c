#include "config.h"

#include "shardsinstaller-disk-entry.h"

struct _ShardsinstallerDiskEntry
{
	GtkToggleButton  parent;

	GtkImage	*disk_type;
	GtkLabel	*disk_name;
	GtkLabel	*disk_size;

	GtkWidget *page;
	char *dev_path;
	char *udisk_path;
	void (*toggle_callback)(GtkWidget *page, const char*);
};

G_DEFINE_FINAL_TYPE (ShardsinstallerDiskEntry, shardsinstaller_disk_entry, GTK_TYPE_TOGGLE_BUTTON)

void
toggle_callback (ShardsinstallerDiskEntry *self) {
	if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (self)) == true)
		self->toggle_callback(self->page, gtk_label_get_label (GTK_LABEL (self->disk_name)));
	return;
}

GtkWidget*
shardsinstaller_disk_entry_new (const char *diskname, const char *size, const gboolean is_spinny, GtkWidget *page, void (*global_toggle_callback)(GtkWidget*, const char*))
{
	ShardsinstallerDiskEntry *self;

	self = g_object_new (SHARDSINSTALLER_TYPE_DISK_ENTRY, NULL);
	self->page = page;
	self->toggle_callback = global_toggle_callback;

	if (!is_spinny)
		gtk_image_set_from_icon_name (self->disk_type, "ssd-symbolic");

	gtk_label_set_label (self->disk_size, strdup(size));
	gtk_label_set_label (self->disk_name, strdup(diskname));
	gtk_label_set_ellipsize (self->disk_name, PANGO_ELLIPSIZE_END);
	gtk_label_set_max_width_chars (self->disk_name, 11);
	if (strlen(diskname) > 11)
		gtk_widget_set_tooltip_text (GTK_WIDGET (self), strdup(diskname));

	return GTK_WIDGET (self);
}

static void
shardsinstaller_disk_entry_class_init (ShardsinstallerDiskEntryClass *klass)
{
	GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

	gtk_widget_class_set_template_from_resource (widget_class, "/projects/shards/installer/widgets/shardsinstaller-disk-entry.ui");
	gtk_widget_class_bind_template_child (widget_class, ShardsinstallerDiskEntry, disk_type);
	gtk_widget_class_bind_template_child (widget_class, ShardsinstallerDiskEntry, disk_name);
	gtk_widget_class_bind_template_child (widget_class, ShardsinstallerDiskEntry, disk_size);
	gtk_widget_class_bind_template_callback (widget_class, toggle_callback);
}

static void
shardsinstaller_disk_entry_init (ShardsinstallerDiskEntry *self)
{
	gtk_widget_init_template (GTK_WIDGET (self));
}
