//密码明文加密EPIN
function EncryptEPin(input)
{
var pk = "C5AEFBE6CEAA9CBEF781C1A093F4670547232718B6AD313EFD908E667E6E3EEA48D65A9C748C20E1995801E3EDDB86F6C1B891920CA54A3DB69BD1CCABFEABC43D3CB6C7BD9A3ACAF7810169F452E375FB3CBB9A6B75EE7C41C249B699BE1B7D5AEA6D9DC6AB81586F1E99A3F3B8C4625CA8956CF50CD2E1C3D8448C6524F9F3";
var encode = document.hsmcli.PkEncryptEPin(input, pk);
return encode;
}
//密码明文加密APIN
function EncryptAPin(input)
{
var pk = "C5AEFBE6CEAA9CBEF781C1A093F4670547232718B6AD313EFD908E667E6E3EEA48D65A9C748C20E1995801E3EDDB86F6C1B891920CA54A3DB69BD1CCABFEABC43D3CB6C7BD9A3ACAF7810169F452E375FB3CBB9A6B75EE7C41C249B699BE1B7D5AEA6D9DC6AB81586F1E99A3F3B8C4625CA8956CF50CD2E1C3D8448C6524F9F3";
var encode = document.hsmcli.PkEncryptAPin(input, pk);
return encode;
}


//请求-结果
function encrypt_1(form,pass)
{
	pass.value =EncryptEPin(pass.value);
	form.submit();
}

//请求-确认-结果
function encrypt_12(form,pass1,pass2)
{
	if(pass1.value==pass2.value)
	{
		pass1.value=EncryptEPin(pass1.value);
		pass2.value=pass1.value;
		form.submit();
		return true;
	}
	else 
		return false;
}

//帐号
function encrypt_acc(form,accpass)
{
	accpass.value=EncryptAPin(accpass.value);
	//document.write(accpass.value);
	//alert(accpass.value);
	form.submit();
}

//请求-确认-结果
function encrypt_1_acc(form,pass1,accpass)
{
	
		pass1.value=EncryptEPin(pass1.value);
		accpass.value=EncryptAPin(accpass.value);
		form.submit();
	
}

//请求-确认-结果
function encrypt_12_acc(form,pass1,pass2,accpass)
{
	if(pass1.value==pass2.value)
	{
		pass1.value=EncryptEPin(pass1.value);
		pass2.value=pass1.value;
		accpass.value=EncryptAPin(accpass.value);
		form.submit();
		return true;
	}
	else 
		return false;
}

function encrypt_012(form,pass0,pass1,pass2)
{
	if(pass1.value==pass2.value)
	{
		pass0.value=EncryptEPin(pass0.value);
		pass1.value=EncryptEPin(pass1.value);
		pass2.value=pass1.value;	
		form.submit();
		return true;
	}
	else 
		return false;
}
