# To change this template, choose Tools | Templates
# and open the template in the editor.
from mysite.polls.models import Poll, Choice
from django.contrib import admin

class ChoiceInline(admin.TabularInline):
    model = Choice
    extra = 5

class PollAdmin(admin.ModelAdmin):

    #get fields in right order + configure
    fieldsets = [
        (None,                  {'fields': ['question']}),
        ('Date information',    {'fields': ['pub_date'], 'classes': ['collapse']})
    ]
    inlines = [ChoiceInline] # tabular choices inline
    list_display = ('question', 'pub_date', 'was_published_today')

    #allow filter query on top level polls page
    list_filter = ['pub_date']
    search_fields = ['question']

class ChoiceAdmin(admin.ModelAdmin):
    fieldsets = [
        ('Choice name', {'fields': ['choice']})
        ]
    list_filter = ['poll']
    search_fields = ['choice']

admin.site.register(Poll, PollAdmin)
admin.site.register(Choice, ChoiceAdmin)



