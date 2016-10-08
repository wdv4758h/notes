#!/bin/sh

PROJECT_NAME="test_celery"

# in the virtualenv

########################################
# Django Project Skeleton
########################################

django-admin startproject $PROJECT_NAME
cd $PROJECT_NAME

########################################
# requirements.txt
########################################

echo -e "django\ncelery" > requirements.txt
pip install -r requirements.txt

########################################
# Project Celery Setting
########################################

echo "from celery import Celery

import os

# set the default Django settings module for the 'celery' program.
os.environ.setdefault('DJANGO_SETTINGS_MODULE', '${PROJECT_NAME}.settings')

from django.conf import settings  # noqa

app = Celery('${PROJECT_NAME}')

# Using a string here means the worker will not have to
# pickle the object when using Windows.
app.config_from_object('django.conf:settings')
app.autodiscover_tasks(lambda: settings.INSTALLED_APPS)" > $PROJECT_NAME/celery.py

echo "
# Celery
BROKER_URL = 'django://'" >> $PROJECT_NAME/settings.py

sed -i "/INSTALLED_APPS = \[/a\    # Celery\n    'kombu.transport.django'," $PROJECT_NAME/settings.py

sed -i "/from django.conf.urls import url/afrom django.conf.urls import include" $PROJECT_NAME/urls.py
sed -i "/urlpatterns = \[/a\    url(r'^myapp/', include('myapp.urls', namespace='myapp'))," $PROJECT_NAME/urls.py

echo "# This will make sure the app is always imported when
# Django starts so that shared_task will use this app.
from .celery import app as celery_app  # noqa" > $PROJECT_NAME/__init__.py

########################################
# Adding Tasks
########################################

./manage.py startapp myapp

sed -i "/INSTALLED_APPS = \[/a\    'myapp'," $PROJECT_NAME/settings.py

echo "class Test(models.Model):
    number = models.IntegerField(default=42)" >> myapp/models.py

echo "from celery import shared_task

@shared_task
def task1():
    print(42)

@shared_task
def task2(model):
    model.number += 1
    model.save()" > myapp/tasks.py

echo "from django.views.generic.edit import CreateView
from django.views.generic.detail import DetailView
from django.core.urlresolvers import reverse
from django.http import JsonResponse
from .models import Test
from .tasks import task1, task2

class TestCreate(CreateView):
    model = Test
    fields = []

    def form_valid(self, form):
        success_url = super(TestCreate, self).form_valid(form)
        return JsonResponse({'result_url': success_url.url})

    def get_success_url(self):
        return reverse('myapp:test_detail', kwargs={'pk': self.object.id})

class TestDetail(DetailView):
    model = Test

    def get(self, request, *args, **kwargs):
        self.object = self.get_object()
        task1.delay()
        task2.delay(self.object)
        return JsonResponse({'number': self.object.number})" >> myapp/views.py

mkdir -p myapp/templates/myapp

echo '<form method="post">{% csrf_token %}{{ form.as_p }}<input type="submit" value="Create" /></form>' > myapp/templates/myapp/test_form.html


echo "from django.conf.urls import patterns, url
from .views import TestDetail, TestCreate

urlpatterns = [
    url(r'^(?P<pk>\d+)$', TestDetail.as_view(), name='test_detail'),
    url(r'^$', TestCreate.as_view(), name='test_create'),
]" > myapp/urls.py


########################################
# Prepare For Running
########################################

./manage.py makemigrations
./manage.py migrate
#./manage.py runserver &
#celery -A $PROJECT_NAME worker -l info &

echo "Please connect to 'http://127.0.0.1:8000/myapp/' to create object"
echo "then connect to 'http://127.0.0.1:8000/myapp/1' to see object detail"
