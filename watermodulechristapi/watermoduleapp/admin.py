from django.contrib import admin

# Register your models here.
from django.http import HttpResponse
import csv
from .models import Tank,Tank_Reading
admin.site.site_header='Christ WaterModule Management'
class ExportCsvMixin:
    def export_as_csv(self, request, queryset):

        meta = self.model._meta
        field_names = [field.name for field in meta.fields]

        response = HttpResponse(content_type='text/csv')
        response['Content-Disposition'] = 'attachment; filename={}.csv'.format(meta)
        writer = csv.writer(response)

        writer.writerow(field_names)
        for obj in queryset:
            row = writer.writerow([getattr(obj, field) for field in field_names])

        return response

    export_as_csv.short_description = "Export Selected"
@admin.register(Tank)
class TankAdmin(admin.ModelAdmin,ExportCsvMixin):
    list_filter = ['Tank_Name','id']
    search_fields = ['Tank_Name','id']
    list_display = ['id','Tank_Name']
    actions = ['export_as_csv']

@admin.register(Tank_Reading)
class TankReadingAdmin(admin.ModelAdmin,ExportCsvMixin):
    list_display = ['Date','Time','Tank_Name','Tank_Reading_Recieved']
    exclude = ['Date','Time','Tank_Name']
    search_fields = ['Date','Time','Tank_Name','Tank_Reading_Recieved']
    list_filter = ['Tank_Name']
    actions = ['export_as_csv']
