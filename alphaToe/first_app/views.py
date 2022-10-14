from django.shortcuts import render
from django.http import HttpResponse
from first_app.models import AccessRecords, Webpage, Topic
# Create your views here.

def index(request):
    webpages_list = AccessRecords.objects.order_by('date')
    date_dict = {
        'AccessRecords': webpages_list,
        }
    return render(request, 'index.html', context=date_dict)
