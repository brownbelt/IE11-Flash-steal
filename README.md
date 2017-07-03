# IE11-Flash-steal

This is unpatched I believe.

IE11 has been fundementally broken for years.

EPM is supposed to restrict read access rights to most folders...

However using the FLASH broker function brokercreatefile with the readonly flag set ... you can read everyfile.

Inject the PoC into IE11, it will try to steal the first .txt file from the documents folder and drop it in favorites (which is write-able by IE11).

There is some buffer issues ... I can't program ... I just make crappy PoCs.
