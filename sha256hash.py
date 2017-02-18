import hashlib

#This is a comment
def hashit(phrase):
	hash = hashlib.sha256()
	hash.update(phrase.encode("utf-8")) #encoding is required otherwise results in exception
	return hash.hexdigest().upper()


print(hashit("mypassword"))
print(hashit("I think therefore I am."))