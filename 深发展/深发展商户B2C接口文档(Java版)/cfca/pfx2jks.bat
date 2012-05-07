@echo off
keytool -delete -alias mykey -keystore merchant.jks -storepass changeit
java -classpath .\lib\sdb.jar;.\lib\jce.jar;.\lib\jcert.jar;.\lib\jnet.jar;.\lib\jsse.jar com.sdb.ebank.bean.PFX2JKS -m 2000000833.pfx 111111
@echo on