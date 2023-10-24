package httputils

type HttpHeader struct {
	header map[string]string
}

type HttpHeaderKeyValue struct {
	K string
	V string
}
type HttpOptions struct {
	Headers *HttpHeader
}

func NewHeader() *HttpHeader {
	return &HttpHeader{header: make(map[string]string)}
}

func NewOptions() *HttpOptions {
	return &HttpOptions{Headers: NewHeader()}
}

func (h *HttpHeader) GetValue(paramKey string) *string {
	value, ok := h.header[paramKey]
	if ok {
		return &value
	} else {
		return nil
	}
}

func (h *HttpHeader) GetKeyValueList() []HttpHeaderKeyValue {
	list := make([]HttpHeaderKeyValue, 0, len(h.header))
	for k, v := range h.header {
		list = append(list, HttpHeaderKeyValue{K: k, V: v})
	}
	return list
}

func (h *HttpHeader) SetValue(paramKey string, paramValue string) {
	h.header[paramKey] = paramValue
}

func JsonPost(paramURL string, paramBody interface{}, paramOptions *HttpOptions) {
	
}
