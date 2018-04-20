# Copy Wt resources
FILE(COPY ${CMAKE_CURRENT_SOURCE_DIR}/trihlav DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
SET(TRIHLAV_DOCROOT ${CMAKE_CURRENT_BINARY_DIR}/docroot)
SET(TRIHLAV_APPROOT ${CMAKE_CURRENT_BINARY_DIR}/approot)
FILE(REMOVE_RECURSE ${TRIHLAV_DOCROOT}/resources)
FILE(REMOVE_RECURSE ${TRIHLAV_APPROOT})
FILE(COPY ${WT_RESOURCES} DESTINATION ${TRIHLAV_DOCROOT} NO_SOURCE_PERMISSIONS)
FILE(COPY ${CMAKE_CURRENT_SOURCE_DIR}/style DESTINATION ${TRIHLAV_DOCROOT})
FILE(COPY ${CMAKE_CURRENT_SOURCE_DIR}/approot DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
INSTALL(DIRECTORY ${TRIHLAV_DOCROOT} DESTINATION share/trihlav)
INSTALL(DIRECTORY ${TRIHLAV_APPROOT} DESTINATION share/approot)
INSTALL(DIRECTORY trihlav DESTINATION /etc)
INSTALL(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/docroot DESTINATION /etc/trihlav)

# openssl req -x509 -newkey rsa:2048 -keyout key.pem -out cert.pem -days XXX
# req
# PKCS#10 certificate request and certificate generating utility.
# 
# -x509
# this option outputs a self signed certificate instead of a certificate request. This is typically used to generate a test certificate or a self signed root CA.
# 
# -newkey arg
# this option creates a new certificate request and a new private key. The argument takes one of several forms. rsa:nbits, where nbits is the number of bits, generates an RSA key nbits in size.
# 
# -keyout filename
# this gives the filename to write the newly created private key to.
# 
# -out filename
# This specifies the output filename to write to or standard output by default.
# 
# -days n
# when the -x509 option is being used this specifies the number of days to certify the certificate for. The default is 30 days.
# 
# -nodes
# if this option is specified then if a private key is created it will not be encrypted.
# 
