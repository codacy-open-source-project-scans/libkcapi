/* Kernel crypto API AF_ALG Asymmetric Cipher API
 *
 * Copyright (C) 2016 - 2024, Stephan Mueller <smueller@chronox.de>
 *
 * License: see COPYING file in root directory
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE, ALL OF
 * WHICH ARE HEREBY DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
 * USE OF THIS SOFTWARE, EVEN IF NOT ADVISED OF THE POSSIBILITY OF SUCH
 * DAMAGE.
 */

#include "internal.h"
#include "kcapi.h"

int kcapi_akcipher_init(struct kcapi_handle **handle, const char *ciphername,
			uint32_t flags)
{
	return _kcapi_handle_init(handle, "akcipher", ciphername, flags);
}

void kcapi_akcipher_destroy(struct kcapi_handle *handle)
{
	_kcapi_handle_destroy(handle);
}

int kcapi_akcipher_setkey(struct kcapi_handle *handle,
			  const uint8_t *key, uint32_t keylen)
{
	return _kcapi_common_setkey(handle, key, keylen);
}

int kcapi_akcipher_setpubkey(struct kcapi_handle *handle,
			     const uint8_t *key, uint32_t keylen)
{
	struct kcapi_handle_tfm *tfm = handle->tfm;
	int ret = 0;

	ret = setsockopt(tfm->tfmfd, SOL_ALG, ALG_SET_PUBKEY, key, keylen);
	return (ret >= 0) ? ret : -errno;
}

IMPL_SYMVER(akcipher_encrypt, "1.3.1")
ssize_t impl_akcipher_encrypt(struct kcapi_handle *handle,
			      const uint8_t *in, size_t inlen,
			      uint8_t *out, size_t outlen, int access)
{
	return _kcapi_cipher_crypt(handle, in, inlen, out, outlen, access,
				   ALG_OP_ENCRYPT);
}

ORIG_SYMVER(akcipher_encrypt, "0.12.0")
int32_t orig_akcipher_encrypt(struct kcapi_handle *handle,
			      const uint8_t *in, uint32_t inlen,
			      uint8_t *out, uint32_t outlen, int access)
{
	return (int32_t)_kcapi_cipher_crypt(handle, in, inlen, out, outlen,
					    access, ALG_OP_ENCRYPT);
}

IMPL_SYMVER(akcipher_decrypt, "1.3.1")
ssize_t impl_akcipher_decrypt(struct kcapi_handle *handle,
			      const uint8_t *in, size_t inlen,
			      uint8_t *out, size_t outlen, int access)
{
	return _kcapi_cipher_crypt(handle, in, inlen, out, outlen, access,
				   ALG_OP_DECRYPT);
}

ORIG_SYMVER(akcipher_decrypt, "0.12.0")
int32_t orig_akcipher_decrypt(struct kcapi_handle *handle,
			      const uint8_t *in, uint32_t inlen,
			      uint8_t *out, uint32_t outlen, int access)
{
	return (int32_t)_kcapi_cipher_crypt(handle, in, inlen, out, outlen,
					    access, ALG_OP_DECRYPT);
}

IMPL_SYMVER(akcipher_sign, "1.3.1")
ssize_t impl_akcipher_sign(struct kcapi_handle *handle,
			   const uint8_t *in, size_t inlen,
			   uint8_t *out, size_t outlen, int access)
{
	return _kcapi_cipher_crypt(handle, in, inlen, out, outlen, access,
				   ALG_OP_SIGN);
}

ORIG_SYMVER(akcipher_sign, "0.12.0")
int32_t orig_akcipher_sign(struct kcapi_handle *handle,
			   const uint8_t *in, uint32_t inlen,
			   uint8_t *out, uint32_t outlen, int access)
{
	return (int32_t)_kcapi_cipher_crypt(handle, in, inlen, out, outlen,
					    access, ALG_OP_SIGN);
}

IMPL_SYMVER(akcipher_verify, "1.3.1")
ssize_t impl_akcipher_verify(struct kcapi_handle *handle,
			     const uint8_t *in, size_t inlen,
			     uint8_t *out, size_t outlen, int access)
{
	return _kcapi_cipher_crypt(handle, in, inlen, out, outlen, access,
				   ALG_OP_VERIFY);
}

ORIG_SYMVER(akcipher_verify, "0.12.0")
int32_t orig_akcipher_verify(struct kcapi_handle *handle,
			     const uint8_t *in, uint32_t inlen,
			     uint8_t *out, uint32_t outlen, int access)
{
	return (int32_t)_kcapi_cipher_crypt(handle, in, inlen, out, outlen,
					    access, ALG_OP_VERIFY);
}

IMPL_SYMVER(akcipher_stream_init_enc, "1.3.1")
ssize_t impl_akcipher_stream_init_enc(struct kcapi_handle *handle,
				      struct iovec *iov, size_t iovlen)
{
	return _kcapi_common_send_meta(handle, iov, iovlen, ALG_OP_ENCRYPT,
				       MSG_MORE);
}

ORIG_SYMVER(akcipher_stream_init_enc, "0.12.0")
int32_t orig_akcipher_stream_init_enc(struct kcapi_handle *handle,
				      struct iovec *iov, uint32_t iovlen)
{
	return (int32_t)_kcapi_common_send_meta(handle, iov, iovlen,
						ALG_OP_ENCRYPT, MSG_MORE);
}

IMPL_SYMVER(akcipher_stream_init_dec, "1.3.1")
ssize_t impl_akcipher_stream_init_dec(struct kcapi_handle *handle,
				      struct iovec *iov, size_t iovlen)
{
	return _kcapi_common_send_meta(handle, iov, iovlen, ALG_OP_DECRYPT,
				       MSG_MORE);
}

ORIG_SYMVER(akcipher_stream_init_dec, "0.12.0")
int32_t orig_akcipher_stream_init_dec(struct kcapi_handle *handle,
				      struct iovec *iov, uint32_t iovlen)
{
	return (int32_t)_kcapi_common_send_meta(handle, iov, iovlen,
						ALG_OP_DECRYPT, MSG_MORE);
}

IMPL_SYMVER(akcipher_stream_init_sgn, "1.3.1")
ssize_t impl_akcipher_stream_init_sgn(struct kcapi_handle *handle,
				      struct iovec *iov, size_t iovlen)
{
	return _kcapi_common_send_meta(handle, iov, iovlen, ALG_OP_SIGN,
				       MSG_MORE);
}

ORIG_SYMVER(akcipher_stream_init_sgn, "0.12.0")
int32_t orig_akcipher_stream_init_sgn(struct kcapi_handle *handle,
				      struct iovec *iov, uint32_t iovlen)
{
	return (int32_t)_kcapi_common_send_meta(handle, iov, iovlen,
						ALG_OP_SIGN, MSG_MORE);
}

IMPL_SYMVER(akcipher_stream_init_vfy, "1.3.1")
ssize_t impl_akcipher_stream_init_vfy(struct kcapi_handle *handle,
				      struct iovec *iov, size_t iovlen)
{
	return _kcapi_common_send_meta(handle, iov, iovlen, ALG_OP_VERIFY,
				       MSG_MORE);
}

ORIG_SYMVER(akcipher_stream_init_vfy, "0.12.0")
int32_t orig_akcipher_stream_init_vfy(struct kcapi_handle *handle,
				      struct iovec *iov, uint32_t iovlen)
{
	return (int32_t)_kcapi_common_send_meta(handle, iov, iovlen,
						ALG_OP_VERIFY, MSG_MORE);
}

IMPL_SYMVER(akcipher_stream_update, "1.3.1")
ssize_t impl_akcipher_stream_update(struct kcapi_handle *handle,
				    struct iovec *iov, size_t iovlen)
{
	if (handle->processed_sg < handle->flags.alg_max_pages)
		return _kcapi_common_vmsplice_iov(handle, iov, iovlen,
						  SPLICE_F_MORE);
	else
		return _kcapi_common_send_data(handle, iov, iovlen, MSG_MORE);
}

ORIG_SYMVER(akcipher_stream_update, "0.12.0")
int32_t orig_akcipher_stream_update(struct kcapi_handle *handle,
				    struct iovec *iov, uint32_t iovlen)
{
	return (int32_t)impl_akcipher_stream_update(handle, iov, iovlen);
}

IMPL_SYMVER(akcipher_stream_update_last, "1.3.1")
ssize_t impl_akcipher_stream_update_last(struct kcapi_handle *handle,
					 struct iovec *iov, size_t iovlen)
{
	if (handle->processed_sg < handle->flags.alg_max_pages)
		return _kcapi_common_vmsplice_iov(handle, iov, iovlen, 0);
	else
		return _kcapi_common_send_data(handle, iov, iovlen, 0);
}

ORIG_SYMVER(akcipher_stream_update_last, "0.12.0")
int32_t orig_akcipher_stream_update_last(struct kcapi_handle *handle,
					 struct iovec *iov, uint32_t iovlen)
{
	return (int32_t)impl_akcipher_stream_update_last(handle, iov, iovlen);
}

IMPL_SYMVER(akcipher_stream_op, "1.3.1")
ssize_t impl_akcipher_stream_op(struct kcapi_handle *handle,
				struct iovec *iov, size_t iovlen)
{
	if (!iov || !iovlen) {
		kcapi_dolog(KCAPI_LOG_ERR,
			    "Asymmetric operation: No buffer for output data provided");
		return -EINVAL;
	}
	return _kcapi_common_recv_data(handle, iov, iovlen);
}

ORIG_SYMVER(akcipher_stream_op, "0.12.0")
int32_t orig_akcipher_stream_op(struct kcapi_handle *handle,
				struct iovec *iov, uint32_t iovlen)
{
	return (int32_t)impl_akcipher_stream_op(handle, iov, iovlen);
}

static ssize_t
_kcapi_akcipher_crypt_aio(struct kcapi_handle *handle, struct iovec *iniov,
			  struct iovec *outiov, size_t iovlen, int access,
			  unsigned int enc)
{
	ssize_t processed = 0, ret;

	/* TODO Every IOVEC is processed as its individual cipher operation. */
	while (iovlen) {
		ret = _kcapi_cipher_crypt_aio(handle, iniov, outiov, 1,
					      access, enc);
		if (ret < 0)
			return ret;

		processed += ret;

		iniov++;
		outiov++;
		iovlen--;
	}

	return processed;
}

/*
 * Fallback function if AIO is not present, but caller requested AIO operation.
 */
static ssize_t
_kcapi_akcipher_encrypt_aio_fallback(struct kcapi_handle *handle,
				     struct iovec *iniov, struct iovec *outiov,
				     size_t iovlen)
{
	size_t i;
	ssize_t ret = kcapi_akcipher_stream_init_enc(handle, NULL, 0);

	if (ret < 0)
		return ret;

	for (i = 0; i < iovlen; i++) {
		ssize_t rc = kcapi_akcipher_stream_update_last(handle, iniov,
							       1);
		if (rc < 0)
			return rc;

		rc = kcapi_akcipher_stream_op(handle, outiov, 1);
		if (rc < 0)
			return rc;

		ret += rc;

		iniov++;
		outiov++;
	}

	return ret;
}

IMPL_SYMVER(akcipher_encrypt_aio, "1.3.1")
ssize_t impl_akcipher_encrypt_aio(struct kcapi_handle *handle,
				  struct iovec *iniov, struct iovec *outiov,
				  size_t iovlen, int access)
{
	ssize_t ret;

	ret = _kcapi_akcipher_crypt_aio(handle, iniov, outiov, iovlen,
					access, ALG_OP_ENCRYPT);
	if (ret != -EOPNOTSUPP)
		return ret;

	return _kcapi_akcipher_encrypt_aio_fallback(handle, iniov, outiov,
						    iovlen);
}

ORIG_SYMVER(akcipher_encrypt_aio, "0.14.0")
int32_t orig_akcipher_encrypt_aio(struct kcapi_handle *handle,
				  struct iovec *iniov, struct iovec *outiov,
				  uint32_t iovlen, int access)
{
	return (int32_t)impl_akcipher_encrypt_aio(handle, iniov, outiov,
						  iovlen, access);
}

/*
 * Fallback function if AIO is not present, but caller requested AIO operation.
 */
static ssize_t
_kcapi_akcipher_decrypt_aio_fallback(struct kcapi_handle *handle,
				     struct iovec *iniov, struct iovec *outiov,
				     size_t iovlen)
{
	uint32_t i;
	ssize_t ret = kcapi_akcipher_stream_init_dec(handle, NULL, 0);

	if (ret < 0)
		return ret;

	for (i = 0; i < iovlen; i++) {
		ssize_t rc = kcapi_akcipher_stream_update_last(handle, iniov,
							       1);
		if (rc < 0)
			return rc;

		rc = kcapi_akcipher_stream_op(handle, outiov, 1);
		if (rc < 0)
			return rc;

		ret += rc;

		iniov++;
		outiov++;
	}

	return ret;
}

IMPL_SYMVER(akcipher_decrypt_aio, "1.3.1")
ssize_t impl_akcipher_decrypt_aio(struct kcapi_handle *handle,
				  struct iovec *iniov, struct iovec *outiov,
				  size_t iovlen, int access)
{
	ssize_t ret;

	ret = _kcapi_akcipher_crypt_aio(handle, iniov, outiov, iovlen,
					access, ALG_OP_DECRYPT);
	if (ret != -EOPNOTSUPP)
		return ret;

	return _kcapi_akcipher_decrypt_aio_fallback(handle, iniov, outiov,
						    iovlen);
}

ORIG_SYMVER(akcipher_decrypt_aio, "0.14.0")
int32_t orig_akcipher_decrypt_aio(struct kcapi_handle *handle,
				  struct iovec *iniov, struct iovec *outiov,
				  uint32_t iovlen, int access)
{
	return (int32_t)impl_akcipher_decrypt_aio(handle, iniov, outiov,
						  iovlen, access);
}

/*
 * Fallback function if AIO is not present, but caller requested AIO operation.
 */
static ssize_t
_kcapi_akcipher_sign_aio_fallback(struct kcapi_handle *handle,
				  struct iovec *iniov, struct iovec *outiov,
				  size_t iovlen)
{
	size_t i;
	ssize_t ret = kcapi_akcipher_stream_init_sgn(handle, NULL, 0);

	if (ret < 0)
		return ret;

	for (i = 0; i < iovlen; i++) {
		ssize_t rc = kcapi_akcipher_stream_update_last(handle, iniov,
							       1);
		if (rc < 0)
			return rc;

		rc = kcapi_akcipher_stream_op(handle, outiov, 1);
		if (rc < 0)
			return rc;

		ret += rc;

		iniov++;
		outiov++;
	}

	return ret;
}

IMPL_SYMVER(akcipher_sign_aio, "1.3.1")
ssize_t impl_akcipher_sign_aio(struct kcapi_handle *handle,
			       struct iovec *iniov, struct iovec *outiov,
			       size_t iovlen, int access)
{
	ssize_t ret;

	ret = _kcapi_akcipher_crypt_aio(handle, iniov, outiov, iovlen,
					access, ALG_OP_SIGN);
	if (ret != -EOPNOTSUPP)
		return ret;

	return _kcapi_akcipher_sign_aio_fallback(handle, iniov, outiov, iovlen);
}

ORIG_SYMVER(akcipher_sign_aio, "0.14.0")
int32_t orig_akcipher_sign_aio(struct kcapi_handle *handle,
			       struct iovec *iniov, struct iovec *outiov,
			       uint32_t iovlen, int access)
{
	return (int32_t)impl_akcipher_sign_aio(handle, iniov, outiov, iovlen,
					       access);
}

/*
 * Fallback function if AIO is not present, but caller requested AIO operation.
 */
static ssize_t
_kcapi_akcipher_verify_aio_fallback(struct kcapi_handle *handle,
				    struct iovec *iniov, struct iovec *outiov,
				    size_t iovlen)
{
	size_t i;
	ssize_t ret = kcapi_akcipher_stream_init_vfy(handle, NULL, 0);

	if (ret < 0)
		return ret;

	for (i = 0; i < iovlen; i++) {
		ssize_t rc = kcapi_akcipher_stream_update_last(handle, iniov,
							       1);
		if (rc < 0)
			return rc;

		rc = kcapi_akcipher_stream_op(handle, outiov, 1);
		if (rc < 0)
			return rc;

		ret += rc;

		iniov++;
		outiov++;
	}

	return ret;
}

IMPL_SYMVER(akcipher_verify_aio, "1.3.1")
ssize_t impl_akcipher_verify_aio(struct kcapi_handle *handle,
				 struct iovec *iniov, struct iovec *outiov,
				 size_t iovlen, int access)
{
	ssize_t ret;

	ret = _kcapi_akcipher_crypt_aio(handle, iniov, outiov, iovlen,
					access, ALG_OP_VERIFY);
	if (ret != -EOPNOTSUPP)
		return ret;

	return _kcapi_akcipher_verify_aio_fallback(handle, iniov, outiov,
						   iovlen);
}

ORIG_SYMVER(akcipher_verify_aio, "0.14.0")
int32_t orig_akcipher_verify_aio(struct kcapi_handle *handle,
				 struct iovec *iniov, struct iovec *outiov,
				 uint32_t iovlen, int access)
{
	return (int32_t)impl_akcipher_verify_aio(handle, iniov, outiov,
						 iovlen, access);
}
