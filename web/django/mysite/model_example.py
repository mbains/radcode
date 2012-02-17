#! /usr/bin/python
from mysite.polls.models import Entry
from mysite.polls.models import Author
from mysite.polls.models import Blog
from mysite.polls.models import Poll
from django.core.exceptions import ObjectDoesNotExist
import datetime


def create():
    Poll.objects.all()
    p = Poll(question="User permissions", pub_date=datetime.datetime.now())

    p.save()
    print p.pub_date
    print p.question
    print p.id

    Poll.objects.all()

def getMethod(id):
    try:
        Poll.objects.get(id=id)
    except ObjectDoesNotExist:
        print "object does not exist"

def setaChoice():
    p = Poll.objects.get(pk=1)
    # @type p Poll
    p.choice_set.create(choice = 'No permissions2', votes = 1)
    p.choice_set.create(choice = 'modify company', votes = 3)
    p.choice_set.create(choice = 'modify global', votes = 2)


def createB(bname='bname'):
    b = Blog(name = bname, tagline='tagline1')
    b.save()

def createEntry(headline, authorName, blogName = "bname"):
    ''' Create entry, set foreign key and update manytomany association'''
    e = Entry(headline=headline, pub_date=datetime.datetime.now())
    b = Blog.objects.get(name=blogName)
    e.blog = b
    e.n_comments = 0
    e.n_pingbacks = 0
    e.rating = 0
    e.save()
    print "created entry, added entry to blog"

    #must use add to add Author because it is a ManyToManyField
    authors = Author.objects.filter(name=authorName)
    if len(authors) == 0:
        author = Author(name=authorName)
        author.save()
    else:
        author = authors[0]

    e.authors.add(author)
    print "added author to entry"
    e.save()

def addAuthorToEntry(entryHeadLine, authorName):
    ''' Add an existing author to an existing entry'''
    e = Entry.objects.get(headline=entryHeadLine)
    a = Author.objects.get(name=authorName)
    e.authors.add(a)

def getEntriesForBlog(blogName):
    blogObj = Blog.objects.get(name=blogName)
    entries = Entry.objects.filter(blog=blogObj)
    print entries

def getAllAuthorsForEntry(entryHeadline):
    entry = Entry.objects.get(headline = entryHeadline)
    authors = entry.authors.all()
    for author in authors:
        # @type author Author
        print author.name

def getAllEntries():
    for entry in Entry.objects.all():
        # @type entry Entry
        print entry.headline

def getAllEntriesForAuthor(authorName):
    for entry in Author.objects.get(name=authorName).entry_set.all():
        print entry.headline


if __name__ ==  '__main__':
    createB()
    createEntry('entrybybob', 'bob')
    Author.objects.create(name='mary')
    addAuthorToEntry('entrybybob', 'mary')
    createEntry('entrybymary', 'mary')
    
