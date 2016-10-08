from django.conf.urls import patterns, url
from .views import TestDetail, TestCreate

urlpatterns = [
    url(r'^(?P<pk>\d+)$', TestDetail.as_view(), name='test_detail'),
    url(r'^$', TestCreate.as_view(), name='test_create'),
]
