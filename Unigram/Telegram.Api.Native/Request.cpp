#include "pch.h"
#include "Request.h"
#include "TLObject.h"
#include "Datacenter.h"

using namespace Telegram::Api::Native;

HRESULT MessageRequest::RuntimeClassInitialize(ITLObject* object, INT64 messageId)
{
	if (object == nullptr)
	{
		return E_INVALIDARG;
	}

	m_object = object;
	m_messageId = messageId;

	return S_OK;
}

HRESULT MessageRequest::get_Object(ITLObject** value)
{
	if (value == nullptr)
	{
		return E_POINTER;
	}

	return m_object.CopyTo(value);
}

HRESULT MessageRequest::get_MessageId(INT64* value)
{
	if (value == nullptr)
	{
		return E_POINTER;
	}

	*value = m_messageId;
	return S_OK;
}


HRESULT GenericRequest::RuntimeClassInitialize(ITLObject* object, INT32 token, ConnectionType connectionType, UINT32 datacenterId, ISendRequestCompletedCallback* sendCompletedCallback,
	IRequestQuickAckReceivedCallback* quickAckReceivedCallback, RequestFlag flags)
{
	m_messageSequenceNumber = 0;
	m_messageToken = token;
	m_connectionType = connectionType;
	m_datacenterId = datacenterId;
	m_sendCompletedCallback = sendCompletedCallback;
	m_quickAckReceivedCallback = quickAckReceivedCallback;
	m_flags = flags;

	return MessageRequest::RuntimeClassInitialize(object, 0);
}

HRESULT GenericRequest::get_RawObject(ITLObject** value)
{
	if (value == nullptr)
	{
		return E_POINTER;
	}

	auto object = GetObject();
	ComPtr<ITLObjectWithQuery> objectWithQuery;
	if (SUCCEEDED(object.As(&objectWithQuery)))
	{
		return objectWithQuery->get_Query(value);
	}

	return object.CopyTo(value);
}

HRESULT GenericRequest::get_MessageSequenceNumber(INT32* value)
{
	if (value == nullptr)
	{
		return E_POINTER;
	}

	*value = m_messageSequenceNumber;
	return S_OK;
}

HRESULT GenericRequest::get_MessageToken(INT32* value)
{
	if (value == nullptr)
	{
		return E_POINTER;
	}

	*value = m_messageToken;
	return S_OK;
}

HRESULT GenericRequest::get_ConnectionType(ConnectionType* value)
{
	if (value == nullptr)
	{
		return E_POINTER;
	}

	*value = m_connectionType;
	return S_OK;
}

HRESULT GenericRequest::get_DatacenterId(UINT32* value)
{
	if (value == nullptr)
	{
		return E_POINTER;
	}

	*value = m_datacenterId;
	return S_OK;
}

HRESULT GenericRequest::get_Flags(RequestFlag* value)
{
	if (value == nullptr)
	{
		return E_POINTER;
	}

	*value = m_flags;
	return S_OK;
}


HRESULT UnencryptedMessageRequest::RuntimeClassInitialize(ITLObject* object, INT64 messageId)
{
	return MessageRequest::RuntimeClassInitialize(object, messageId);
}