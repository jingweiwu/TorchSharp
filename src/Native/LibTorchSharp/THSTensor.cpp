// Copyright (c) Microsoft Corporation and contributors.  All Rights Reserved.  See License.txt in the project root for license information.
#include "THSTensor.h"

#include <iostream>
#include <fstream>

Tensor THSTensor_arange(
    const Scalar start,
    const Scalar end,
    const Scalar step,
    const int8_t scalar_type,
    const int device_type, const int device_index,
    const bool requires_grad)
{
    auto options = at::TensorOptions()
        .dtype(at::ScalarType(scalar_type))
        .device(c10::Device((c10::DeviceType)device_type, (c10::DeviceIndex)device_index))
        .requires_grad(requires_grad);

    CATCH_TENSOR(torch::arange(*start, *end, *step, options));
}

Tensor THSTensor_zeros(
    const int64_t * sizes,
    const int length,
    const int8_t scalar_type,
    const int device_type, const int device_index,
    const bool requires_grad)
{
    auto options = at::TensorOptions()
        .dtype(at::ScalarType(scalar_type))
        .device(c10::Device((c10::DeviceType)device_type, (c10::DeviceIndex)device_index))
        .requires_grad(requires_grad);

    CATCH_TENSOR(torch::zeros(at::ArrayRef<int64_t>(sizes, length), options));
}

Tensor THSTensor_ones(
    const int64_t * sizes,
    const int length,
    const int8_t scalar_type,
    const int device_type, const int device_index,
    const bool requires_grad)
{
    auto options = at::TensorOptions()
        .dtype(at::ScalarType(scalar_type))
        .device(c10::Device((c10::DeviceType)device_type, (c10::DeviceIndex)device_index))
        .requires_grad(requires_grad);

    CATCH_TENSOR(torch::ones(at::ArrayRef<int64_t>(sizes, length), options));
}

Tensor THSTensor_empty(
    const int64_t * sizes,
    const int length,
    const int8_t scalar_type,
    const int device_type, const int device_index,
    const bool requires_grad)
{
    auto options = at::TensorOptions()
        .dtype(at::ScalarType(scalar_type))
        .device(c10::Device((c10::DeviceType)device_type, (c10::DeviceIndex)device_index))
        .requires_grad(requires_grad);

    CATCH_TENSOR(torch::empty(at::ArrayRef<int64_t>(sizes, length), options));
}

Tensor THSTensor_new(
    void * data, 
    void (*deleter)(void *),
    const int64_t * sizes, 
    const int szlength, 
    int8_t scalar_type,
    const bool requires_grad)
{
    auto options = at::TensorOptions()
        .dtype(at::ScalarType(scalar_type))
        .requires_grad(requires_grad);

    CATCH_TENSOR(torch::from_blob(data, at::ArrayRef<int64_t>(sizes, szlength), deleter, options));
}

Tensor THSTensor_newLong(
    int64_t * data,
    void (*deleter)(void*),
    const int64_t * sizes,
    const int szlength,
    const bool requires_grad)
{
    auto options = at::TensorOptions()
        .dtype(at::ScalarType(at::kLong))
        .requires_grad(requires_grad);
    CATCH_TENSOR(torch::from_blob(data, at::ArrayRef<int64_t>(sizes, szlength), deleter, options));
}

// The data is passed in as float and copied into the array of Half in the C++ code
// since .NET doesn't know about 'half' values.
Tensor THSTensor_newHalf(
    float* rawArray,
    c10::Half* dataArray,
    void (*deleter)(void*),
    const int64_t* sizes,
    const int szlength,
    const bool requires_grad)
{
    CATCH_RETURN_Tensor(
        int64_t sz = 1;
        for (int k = 0; k < szlength; k++)
            sz *= sizes[k];
        for (int64_t i = 0; i < sz; i++)
            dataArray[i] = (c10::Half)rawArray[i];
        auto options = at::TensorOptions()
            .dtype(at::ScalarType(at::kHalf))
            .requires_grad(requires_grad);
        res = ResultTensor(torch::from_blob(dataArray, at::ArrayRef<int64_t>(sizes, szlength), deleter, options));
    )
}

Tensor THSTensor_newSByteScalar(int8_t data, bool requires_grad)
{
    auto options = at::TensorOptions()
        .dtype(at::ScalarType(c10::ScalarType::Char))
        .requires_grad(requires_grad);
    CATCH_TENSOR(torch::tensor(data, options));
}

Tensor THSTensor_newByteScalar(char data, bool requires_grad)
{
    auto options = at::TensorOptions()
        .dtype(at::ScalarType(c10::ScalarType::Byte))
        .requires_grad(requires_grad);
    CATCH_TENSOR(torch::tensor(data, options));
}

Tensor THSTensor_newBoolScalar(bool  data, bool requires_grad)
{
    auto options = at::TensorOptions()
        .dtype(at::ScalarType(c10::ScalarType::Bool))
        .requires_grad(requires_grad);
    CATCH_TENSOR(torch::tensor(data, options));
}

Tensor THSTensor_newHalfScalar(float data, bool requires_grad)
{
    auto options = at::TensorOptions()
        .dtype(at::ScalarType(c10::ScalarType::Half))
        .requires_grad(requires_grad);
    CATCH_TENSOR(torch::tensor((c10::Half)data, options));
}

Tensor THSTensor_newShortScalar(short data, bool requires_grad)
{
    auto options = at::TensorOptions()
        .dtype(at::ScalarType(c10::ScalarType::Short))
        .requires_grad(requires_grad);
    CATCH_TENSOR(torch::tensor(data, options));
}

Tensor THSTensor_newIntScalar(int data, bool requires_grad)
{
    auto options = at::TensorOptions()
        .dtype(at::ScalarType(c10::ScalarType::Int))
        .requires_grad(requires_grad);
    CATCH_TENSOR(torch::tensor(data, options));
}

Tensor THSTensor_newLongScalar(int64_t data, bool requires_grad)
{
    auto options = at::TensorOptions()
        .dtype(at::ScalarType(c10::ScalarType::Long))
        .requires_grad(requires_grad);
    CATCH_TENSOR(torch::tensor(data, options));
}

Tensor THSTensor_newDoubleScalar(double data, bool requires_grad)
{
    auto options = at::TensorOptions()
        .dtype(at::ScalarType(c10::ScalarType::Double))
        .requires_grad(requires_grad);
    CATCH_TENSOR(torch::tensor(data, options));
}

Tensor THSTensor_newFloatScalar(float data, bool requires_grad)
{
    auto options = at::TensorOptions()
        .dtype(at::ScalarType(c10::ScalarType::Float))
        .requires_grad(requires_grad);
    CATCH_TENSOR(torch::tensor(data, options));
}

Tensor THSTensor_rand(
    const int64_t * sizes,
    const int length,
    const int8_t scalar_type,
    const int device_type, const int device_index,
    const bool requires_grad)
{
    Tensor tensor;
    CATCH(
        auto options = at::TensorOptions()
            .dtype(at::ScalarType(scalar_type))
            .device(c10::Device((c10::DeviceType)device_type, (c10::DeviceIndex)device_index))
            .requires_grad(requires_grad);

        tensor = new torch::Tensor(torch::rand(at:: ArrayRef<int64_t>(sizes, length), options));
    )
    return tensor;
}

Tensor THSTensor_randint(
    const int64_t max,
    const int64_t* sizes,
    const int length,
    const int8_t scalar_type,
    const int device_type, const int device_index,
    const bool requires_grad)
{
    Tensor tensor;
    CATCH(
        auto options = at::TensorOptions()
        .dtype(at::ScalarType(scalar_type))
        .device(c10::Device((c10::DeviceType)device_type, (c10::DeviceIndex)device_index))
        .requires_grad(requires_grad);

        tensor = new torch::Tensor(torch::randint(max, at::ArrayRef<int64_t>(sizes, length), options));
    )
    return tensor;
}

Tensor THSTensor_randn(
    const int64_t * sizes,
    const int length,
    const int8_t scalar_type,
    const int device_type, const int device_index,
    const bool requires_grad)
{
    auto options = at::TensorOptions()
        .dtype(at::ScalarType(scalar_type))
        .device(c10::Device((c10::DeviceType)device_type, (c10::DeviceIndex)device_index))
        .requires_grad(requires_grad);

    CATCH_TENSOR(torch::randn(at::ArrayRef<int64_t>(sizes, length), options));
}

Tensor THSTensor_sparse(
    Tensor indices,
    Tensor values,
    const int64_t * sizes,
    const int length,
    const int8_t scalar_type,
    const int device_type, const int device_index,
    const bool requires_grad)
{
    auto options = at::TensorOptions()
        .dtype(at::ScalarType(scalar_type))
        .device(c10::Device((c10::DeviceType)device_type, (c10::DeviceIndex)device_index))
        .requires_grad(requires_grad);

	const torch::autograd::Variable& vindices = torch::autograd::as_variable_ref(*indices);
	const torch::autograd::Variable& vvalues = torch::autograd::as_variable_ref(*values);
	at::Tensor i = vindices.tensor_data();
	at::Tensor v = vvalues.tensor_data();

    CATCH_TENSOR(torch::sparse_coo_tensor(i, v, at::ArrayRef<int64_t>(sizes, length), options));
}

int64_t THSTensor_ndimension(const Tensor tensor)
{
    CATCH_RETURN(int64_t, 0, tensor->ndimension());
}

int64_t THSTensor_stride(const Tensor tensor, const int64_t dimension)
{
    CATCH_RETURN(int64_t, 0, tensor->stride(dimension));
}

int64_t* THSTensor_strides(const Tensor tensor)
{
    CATCH_RETURN(int64_t *, NULL, tensor->strides().vec().data());
}

int64_t THSTensor_size(const Tensor tensor, const int64_t dimension)
{
    CATCH_RETURN(int64_t, 0, tensor->size(dimension));
}

//void THSTensor_sizes(const Tensor tensor, int64_t* (*allocator)(size_t length))
//{
//    CATCH(
//        auto res = tensor->sizes();
//        const size_t sz = res.size();
//        int64_t* result = allocator(sz);
//        for (size_t i = 0; i < sz; i++)
//            result[i] = res[i];
//    )
//}

void THSTensor_dispose(const Tensor tensor)
{
    delete tensor;
}

void * THSTensor_data(const Tensor tensor)
{
    CATCH_RETURN(void *, NULL, tensor->data_ptr());
}

float THSTensor_data_idx_half(const Tensor tensor, const int64_t i)
{
    CATCH_RETURN(float, NULL, (float)(tensor->data_ptr<c10::Half>())[i]);
}

Scalar THSTensor_item(const Tensor tensor)
{
    CATCH_RETURN(Scalar, NULL, new torch::Scalar(tensor->item()));
}

Tensor THSTensor_get1(const Tensor tensor, int64_t index)
{
    CATCH_TENSOR((*tensor)[index]);
}

Tensor THSTensor_get2(const Tensor tensor, int64_t index1, int64_t index2)
{
    CATCH_TENSOR((*tensor)[index1][index2]);
}

Tensor THSTensor_get3(const Tensor tensor, int64_t index1, int64_t index2, int64_t index3)
{
    CATCH_TENSOR((*tensor)[index1][index2][index3]);
}

Tensor THSTensor_get4(const Tensor tensor, int64_t index1, int64_t index2, int64_t index3, int64_t index4)
{
    CATCH_TENSOR((*tensor)[index1][index2][index3][index4]);
}

void THSTensor_set1(const Tensor tensor, int64_t index, Scalar value)
{
    CATCH(
        (*tensor)[index] = *value;
    )
}

void THSTensor_set2(const Tensor tensor, int64_t index1, int64_t index2, Scalar value)
{
    CATCH(
        (*tensor)[index1][index2] = *value;
    )
}

void THSTensor_set3(const Tensor tensor, int64_t index1, int64_t index2, int64_t index3, Scalar value)
{
    CATCH(
        (*tensor)[index1][index2][index3] = *value;
    )
}

void THSTensor_set4(const Tensor tensor, int64_t index1, int64_t index2, int64_t index3, int64_t index4, Scalar value)
{
    CATCH(
        (*tensor)[index1][index2][index3][index4] = *value;
    )
}

int8_t THSTensor_type(const Tensor tensor)
{
    CATCH_RETURN(int8_t, 0, (int8_t)tensor->scalar_type());
}

Tensor THSTensor_to_type(const Tensor tensor, int8_t scalar_type)
{
    CATCH_TENSOR(tensor->toType(at::ScalarType(scalar_type)));
}

const char* THSTensor_device_str(const Tensor tensor)
{
    auto device = tensor->device();

    return make_sharable_string(device.str());
}

int THSTensor_device_index(const Tensor tensor)
{
    auto device = tensor->device();
    return device.index();
}

int THSTensor_device_type(const Tensor tensor)
{
    auto device = tensor->device();
    return (int)device.type();
}

int THSTensor_requires_grad(const Tensor tensor)
{
    CATCH_RETURN(int, 0, tensor->requires_grad());
}

Tensor THSTensor_set_requires_grad(const Tensor tensor, const bool requires_grad)
{
   CATCH_TENSOR(tensor->set_requires_grad(requires_grad));
}

int THSTensor_is_sparse(const Tensor tensor)
{
    CATCH_RETURN(int, 0, tensor->is_sparse());
}

Tensor THSTensor_indices(Tensor tensor)
{
    CATCH_TENSOR(tensor->_indices());
}

Tensor THSTensor_values(Tensor tensor)
{
    CATCH_TENSOR(tensor->_values());
}

Tensor THSTensor_cpu(const Tensor tensor)
{
    CATCH_TENSOR(tensor->cpu());
}

Tensor THSTensor_cuda(const Tensor tensor)
{
    CATCH_TENSOR(tensor->cuda());
}

Tensor THSTensor_to_device(const Tensor tensor, const int device_type, const int device_index)
{
    CATCH_RETURN_Tensor(
        auto device = c10::Device((c10::DeviceType)device_type, (c10::DeviceIndex)device_index);
        res = ResultTensor(tensor->to(device));
    );
}

Tensor THSTensor_load(const char* location)
{
    CATCH_RETURN_Tensor(
        torch::Tensor tensor;
        torch::load(tensor, location);
        res = ResultTensor(tensor);
    );
}

void THSTensor_save(const Tensor tensor, const char* location)
{
    CATCH(
        torch::save(*tensor, location);
    );
}


Tensor THSTensor_grad(const Tensor tensor)
{
    Tensor res;
    CATCH(
        torch::Tensor grad = tensor->grad();
        res = grad.defined() ? new torch::Tensor(grad) : NULL;
    );
    return res;
}

void THSTensor_backward(Tensor tensor)
{
    CATCH (
        tensor->backward();
    )
}

Tensor THSTensor_to_dense(Tensor tensor)
{
    CATCH_TENSOR(tensor->to_dense());
}

Tensor THSTensor_cat(const Tensor* tensors, const int length, const int64_t dim)
{
    CATCH_TENSOR(torch::cat(toTensors<at::Tensor>((torch::Tensor**)tensors, length), dim));
}

Tensor THSTensor_clone(const Tensor input)
{
    CATCH_TENSOR(input->clone());
}

Tensor THSTensor_contiguous(const Tensor input)
{
    CATCH_TENSOR(input->contiguous());
}

Tensor THSTensor_index_select(Tensor tensor, int64_t dimension, Tensor index)
{
    CATCH_TENSOR(tensor->index_select(dimension, *index));
}

Tensor THSTensor_squeeze(Tensor tensor, int64_t dimension)
{
    CATCH_TENSOR(tensor->squeeze(dimension));
}

Tensor THSTensor_reshape(const Tensor tensor, const int64_t * shape, const int length)
{
    CATCH_TENSOR(tensor->reshape(at::ArrayRef<int64_t>(shape, length)));
}

Tensor THSTensor_stack(const Tensor* tensors, const int length, const int64_t dim)
{
    CATCH_TENSOR(torch::stack(toTensors<at::Tensor>((torch::Tensor**)tensors, length), dim));
}

Tensor THSTensor_t(const Tensor tensor)
{
    CATCH_TENSOR(tensor->t());
}

Tensor THSTensor_transpose(const Tensor tensor, const int64_t dim1, const int64_t dim2)
{
    CATCH_TENSOR(tensor->transpose(dim1, dim2));
}

Tensor THSTensor_transpose_(const Tensor tensor, const int64_t dim1, const int64_t dim2)
{
    CATCH_TENSOR(tensor->transpose_(dim1, dim2));
}

Tensor THSTensor_view(const Tensor tensor, const int64_t * shape, const int length)
{
    CATCH_TENSOR(tensor->view(at::ArrayRef<int64_t>(shape, length)));
}

Tensor THSTensor_add(const Tensor left, const Tensor right, const Scalar alpha)
{
    CATCH_TENSOR(left->add(*right, *alpha));
}

Tensor THSTensor_add_(const Tensor left, const Tensor right, const Scalar alpha)
{
    CATCH_TENSOR(left->add_(*right, *alpha));
}

Tensor THSTensor_addS(const Tensor left, const Scalar right, const Scalar alpha)
{
    CATCH_TENSOR(left->add(*right, *alpha));
}

Tensor THSTensor_addS_(const Tensor left, const Scalar right, const Scalar alpha)
{
    CATCH_TENSOR(left->add_(*right, *alpha));
}

Tensor THSTensor_addbmm(
    const Tensor mat,
    const Tensor batch1,
    const Tensor batch2,
    const float beta,
    const float alpha)
{
    CATCH_TENSOR(mat->addbmm(*batch1, *batch2, beta, alpha));
}

Tensor THSTensor_addmm(
    const Tensor mat,
    const Tensor mat1,
    const Tensor mat2,
    const float beta,
    const float alpha)
{
    CATCH_TENSOR(mat->addmm(*mat1, *mat2, beta, alpha));
}

Tensor THSTensor_argmaxT(const Tensor tensor, const int64_t dimension, bool keepDim)
{
    CATCH_TENSOR(tensor->argmax(dimension, keepDim));
}

Tensor THSTensor_argmax(const Tensor tensor)
{
    CATCH_TENSOR(tensor->argmax());
}

void THSTensor_topk(const Tensor tensor, Tensor* (*allocator)(size_t length), const int k, const int64_t dimension, const bool largest, const bool sorted)
{
    CATCH (
        auto topk = tensor->topk(k, dimension, largest, sorted);
        Tensor* result = allocator(2);
        result[0] = new torch::Tensor(std::get<0>(topk));
        result[1] = new torch::Tensor(std::get<1>(topk));
    )
}

Tensor THSTensor_argminT(const Tensor tensor, const int64_t dimension, bool keepDim)
{
    CATCH_TENSOR(tensor->argmin(dimension, keepDim));
}

Tensor THSTensor_argmin(const Tensor tensor)
{
    CATCH_TENSOR(tensor->argmin());
}

Tensor THSTensor_relu(const Tensor tensor)
{
    CATCH_TENSOR(tensor->relu());
}

Tensor THSTensor_relu_(const Tensor tensor)
{
    CATCH_TENSOR(tensor->relu_());
}

Tensor THSTensor_bernoulli(const Tensor tensor, const double p)
{
    CATCH_TENSOR(tensor->bernoulli(p));
}

Tensor THSTensor_bernoulli_(const Tensor tensor, const double p)
{
    CATCH_TENSOR(tensor->bernoulli_(p));
}

Tensor THSTensor_cauchy_(const Tensor tensor, const double median, const double sigma)
{
    CATCH_TENSOR(tensor->cauchy_(median, sigma));
}

Tensor THSTensor_exponential_(const Tensor tensor, const double lambd)
{
    CATCH_TENSOR(tensor->exponential_(lambd));
}

Tensor THSTensor_geometric_(const Tensor tensor, const double p)
{
    CATCH_TENSOR(tensor->geometric_(p));
}

Tensor THSTensor_log_normal_(const Tensor tensor, const double mean, const double std)
{
    CATCH_TENSOR(tensor->log_normal_(mean, std));
}

Tensor THSTensor_normal_(const Tensor tensor, const double mean, const double std)
{
    CATCH_TENSOR(tensor->normal_(mean, std));
}

Tensor THSTensor_uniform_(const Tensor tensor, const double from, const double to)
{
    CATCH_TENSOR(tensor->uniform_(from, to));
}

Tensor THSTensor_randperm(const int64_t n,
    const int8_t scalar_type,
    const int device_type, const int device_index,
    const bool requires_grad)
{
    Tensor tensor;
    CATCH(
        auto options =
            at::TensorOptions()
            .dtype(at::ScalarType(scalar_type))
            .device(c10::Device((c10::DeviceType)device_type, (c10::DeviceIndex)device_index))
            .requires_grad(requires_grad);

        tensor = new torch::Tensor(torch::randperm(n, options));
    )
    return tensor;
}

Tensor THSTensor_multinomial(const Tensor tensor, const double num_samples, const bool replacement)
{
    CATCH_TENSOR(tensor->multinomial(num_samples, replacement));
}


Tensor THSTensor_acos(const Tensor tensor)
{
    CATCH_TENSOR(tensor->acos());
}

Tensor THSTensor_acos_(const Tensor tensor)
{
    CATCH_TENSOR(tensor->acos_());
}

Tensor THSTensor_asin(const Tensor tensor)
{
    CATCH_TENSOR(tensor->asin());
}

Tensor THSTensor_asin_(const Tensor tensor)
{
    CATCH_TENSOR(tensor->asin_());
}

Tensor THSTensor_atan(const Tensor tensor)
{
    CATCH_TENSOR(tensor->atan());
}

Tensor THSTensor_atan_(const Tensor tensor)
{
    CATCH_TENSOR(tensor->atan_());
}

Tensor THSTensor_sin(const Tensor tensor)
{
    CATCH_TENSOR(tensor->sin());
}

Tensor THSTensor_sin_(const Tensor tensor)
{
    CATCH_TENSOR(tensor->sin_());
}

Tensor THSTensor_cos(const Tensor tensor)
{
    CATCH_TENSOR(tensor->cos());
}

Tensor THSTensor_cos_(const Tensor tensor)
{
    CATCH_TENSOR(tensor->cos_());
}

Tensor THSTensor_tan(const Tensor tensor)
{
    CATCH_TENSOR(tensor->tan());
}

Tensor THSTensor_tan_(const Tensor tensor)
{
    CATCH_TENSOR(tensor->tan_());
}

Tensor THSTensor_sinh(const Tensor tensor)
{
    CATCH_TENSOR(tensor->sinh());
}

Tensor THSTensor_sinh_(const Tensor tensor)
{
    CATCH_TENSOR(tensor->sinh_());
}

Tensor THSTensor_cosh(const Tensor tensor)
{
    CATCH_TENSOR(tensor->cosh());
}

Tensor THSTensor_cosh_(const Tensor tensor)
{
    CATCH_TENSOR(tensor->cosh_());
}

Tensor THSTensor_tanh(const Tensor tensor)
{
    CATCH_TENSOR(tensor->tanh());
}

Tensor THSTensor_tanh_(const Tensor tensor)
{
    CATCH_TENSOR(tensor->tanh_());
}

Tensor THSTensor_floor(const Tensor tensor)
{
    CATCH_TENSOR(tensor->floor());
}

Tensor THSTensor_floor_(const Tensor tensor)
{
    CATCH_TENSOR(tensor->floor_());
}

Tensor THSTensor_ceil(const Tensor tensor)
{
    CATCH_TENSOR(tensor->ceil());
}

Tensor THSTensor_ceil_(const Tensor tensor)
{
    CATCH_TENSOR(tensor->ceil_());
}

Tensor THSTensor_abs(const Tensor tensor)
{
    CATCH_TENSOR(tensor->abs());
}

Tensor THSTensor_abs_(const Tensor tensor)
{
    CATCH_TENSOR(tensor->abs_());
}

Tensor THSTensor_round(const Tensor tensor)
{
    CATCH_TENSOR(tensor->round());
}

Tensor THSTensor_round_(const Tensor tensor)
{
    CATCH_TENSOR(tensor->round_());
}

Tensor THSTensor_sign(const Tensor tensor)
{
    CATCH_TENSOR(tensor->sign());
}

Tensor THSTensor_sign_(const Tensor tensor)
{
    CATCH_TENSOR(tensor->sign_());
}

Tensor THSTensor_sqrt(const Tensor tensor)
{
    CATCH_TENSOR(tensor->sqrt());
}

Tensor THSTensor_sqrt_(const Tensor tensor)
{
    CATCH_TENSOR(tensor->sqrt_());
}

Tensor THSTensor_softplus(const Tensor tensor)
{
    CATCH_TENSOR(torch::softplus(*tensor));
}

Tensor THSTensor_neg(const Tensor tensor)
{
    CATCH_TENSOR(tensor->neg());
}

Tensor THSTensor_neg_(const Tensor tensor)
{
    CATCH_TENSOR(tensor->neg_());
}

Tensor THSTensor_pow(const Tensor tensor, const Tensor exponent)
{
    CATCH_TENSOR(tensor->pow(*exponent));
}

Tensor THSTensor_pow_(const Tensor tensor, const Tensor exponent)
{
    CATCH_TENSOR(tensor->pow_(*exponent));
}

Tensor THSTensor_powS(const Tensor tensor, const Scalar exponent)
{
    CATCH_TENSOR(tensor->pow(*exponent));
}

Tensor THSTensor_powS_(const Tensor tensor, const Scalar exponent)
{
    CATCH_TENSOR(tensor->pow_(*exponent));
}

Tensor THSTensor_fill_(const Tensor tensor, const Scalar value)
{
    CATCH_TENSOR(tensor->fill_(*value));
}

Tensor THSTensor_baddbmm(
    const Tensor batch1,
    const Tensor batch2,
    const Tensor mat,
    const float beta,
    const float alpha)
{
    CATCH_TENSOR(mat->baddbmm(*batch1, *batch2, beta, alpha));
}

Tensor THSTensor_bmm(const Tensor batch1, const Tensor batch2)
{
    CATCH_TENSOR(batch1->bmm(*batch2));
}

Tensor THSTensor_clamp(const Tensor input, const Scalar min, const Scalar max)
{
    CATCH_TENSOR(input->clamp(*min, *max));
}

Tensor THSTensor_div(const Tensor left, const Tensor right)
{
    CATCH_TENSOR(left->div(*right));
}

Tensor THSTensor_div_(const Tensor left, const Tensor right)
{
    CATCH_TENSOR(left->div_(*right));
}

Tensor THSTensor_divS(const Tensor left, const Scalar right)
{
    CATCH_TENSOR(left->div(*right));
}

Tensor THSTensor_divS2(const Scalar left, const Tensor right)
{
    CATCH_TENSOR(at::empty(right->sizes(), right->options()).fill_(*left).div_(*right));
}

Tensor THSTensor_divS_(const Tensor left, const Scalar right)
{
    CATCH_TENSOR(left->div_(*right));
}

Tensor THSTensor_eq(const Tensor left, const Tensor right)
{
    CATCH_TENSOR(left->eq(*right));
}

Tensor THSTensor_eq_(const Tensor left, const Tensor right)
{
    CATCH_TENSOR(left->eq_(*right));
}

Tensor THSTensor_eqS(const Tensor left, const Scalar right)
{
    CATCH_TENSOR(left->eq(*right));
}

Tensor THSTensor_eqS_(const Tensor left, const Scalar right)
{
    CATCH_TENSOR(left->eq_(*right));
}

int THSTensor_equal(const Tensor left, const Tensor right)
{
    CATCH_RETURN(int, 0, left->equal(*right));
}

int THSTensor_allclose(const Tensor left, const Tensor right, double rtol, double atol, bool equal_nan)
{
    CATCH_RETURN(int, 0, left->allclose(*right, rtol, atol, equal_nan));
}

Tensor THSTensor_exp(const Tensor tensor)
{
    CATCH_TENSOR(tensor->exp());
}

Tensor THSTensor_erf(const Tensor tensor)
{
    CATCH_TENSOR(tensor->erf());
}

Tensor THSTensor_erf_(const Tensor tensor)
{
    CATCH_TENSOR(tensor->erf_());
}

Tensor THSTensor_ge(const Tensor left, const Tensor right)
{
    CATCH_TENSOR(left->ge(*right));
}

Tensor THSTensor_ge_(const Tensor left, const Tensor right)
{
    CATCH_TENSOR(left->ge_(*right));
}

Tensor THSTensor_geS(const Tensor left, const Scalar right)
{
    CATCH_TENSOR(left->ge(*right));
}

Tensor THSTensor_geS_(const Tensor left, const Scalar right)
{
    CATCH_TENSOR(left->ge_(*right));
}

Tensor THSTensor_gt(const Tensor left, const Tensor right)
{
    CATCH_TENSOR(left->gt(*right));
}

Tensor THSTensor_gt_(const Tensor left, const Tensor right)
{
    CATCH_TENSOR(left->gt_(*right));
}

Tensor THSTensor_gtS(const Tensor left, const Scalar right)
{
    CATCH_TENSOR(left->gt(*right));
}

Tensor THSTensor_gtS_(const Tensor left, const Scalar right)
{
    CATCH_TENSOR(left->gt_(*right));
}

Tensor THSTensor_le(const Tensor left, const Tensor right)
{
    CATCH_TENSOR(left->le(*right));
}

Tensor THSTensor_le_(const Tensor left, const Tensor right)
{
    CATCH_TENSOR(left->le_(*right));
}

Tensor THSTensor_leS(const Tensor left, const Scalar right)
{
    CATCH_TENSOR(left->le(*right));
}

Tensor THSTensor_leS_(const Tensor left, const Scalar right)
{
    CATCH_TENSOR(left->le_(*right));
}

Tensor THSTensor_log(const Tensor tensor)
{
    CATCH_TENSOR(tensor->log());
}

Tensor THSTensor_log_(const Tensor tensor)
{
    CATCH_TENSOR(tensor->log_());
}

Tensor THSTensor_log2(const Tensor tensor)
{
    CATCH_TENSOR(tensor->log());
}

Tensor THSTensor_log2_(const Tensor tensor)
{
    CATCH_TENSOR(tensor->log_());
}

Tensor THSTensor_log10(const Tensor tensor)
{
    CATCH_TENSOR(tensor->log10());
}

Tensor THSTensor_log10_(const Tensor tensor)
{
    CATCH_TENSOR(tensor->log10_());
}

Tensor THSTensor_lt(const Tensor left, const Tensor right)
{
    CATCH_TENSOR(left->lt(*right));
}

Tensor THSTensor_lt_(const Tensor left, const Tensor right)
{
    CATCH_TENSOR(left->lt_(*right));
}

Tensor THSTensor_ltS(const Tensor left, const Scalar right)
{
    CATCH_TENSOR(left->lt(*right));
}

Tensor THSTensor_ltS_(const Tensor left, const Scalar right)
{
    CATCH_TENSOR(left->lt_(*right));
}

Tensor THSTensor_matmul(const Tensor left, const Tensor right)
{
    return  new torch::Tensor(left->matmul(*right));
}

void THSTensor_max(const Tensor tensor, Tensor* (*allocator)(size_t length), const int64_t dimension, const bool keep_dim)
{
    auto max = tensor->max(dimension, keep_dim);
    Tensor * result = allocator(2);
    result[0] = new torch::Tensor(std::get<0>(max));
    result[1] = new torch::Tensor(std::get<1>(max));
}

Tensor THSTensor_mean(const Tensor tensor)
{
    CATCH_TENSOR(tensor->mean());
}

Tensor THSTensor_mm(const Tensor left, const Tensor right)
{
    CATCH_TENSOR(left->mm(*right));
}

Tensor THSTensor_mul(const Tensor left, const Tensor right)
{
    CATCH_TENSOR(left->mul(*right));
}

Tensor THSTensor_mul_(const Tensor left, const Tensor right)
{
    CATCH_TENSOR(left->mul_(*right));
}

Tensor THSTensor_mulS(const Tensor tensor, const Scalar scalar)
{
    CATCH_TENSOR(tensor->mul(*scalar));
}

Tensor THSTensor_mulS_(const Tensor tensor, const Scalar scalar)
{
    CATCH_TENSOR(tensor->mul_(*scalar));
}

Tensor THSTensor_ne(const Tensor left, const Tensor right)
{
    CATCH_TENSOR(left->ne(*right));
}

Tensor THSTensor_ne_(const Tensor left, const Tensor right)
{
    CATCH_TENSOR(left->ne_(*right));
}

Tensor THSTensor_neS(const Tensor left, const Scalar right)
{
    CATCH_TENSOR(left->ne(*right));
}

Tensor THSTensor_neS_(const Tensor left, const Scalar right)
{
    CATCH_TENSOR(left->ne_(*right));
}

Tensor THSTensor_norm(const Tensor tensor, const int64_t dimension, const bool keep_dimension)
{
    CATCH_TENSOR(tensor->norm(0, dimension, keep_dimension));
}

Tensor THSTensor_remainder(const Tensor left, const Tensor right)
{
    CATCH_TENSOR(left->remainder(*right));
}

Tensor THSTensor_remainder_(const Tensor left, const Tensor right)
{
    CATCH_TENSOR(left->remainder_(*right));
}

Tensor THSTensor_remainderS(const Tensor left, const Scalar right)
{
    CATCH_TENSOR(left->remainder(*right));
}

Tensor THSTensor_remainderS_(const Tensor left, const Scalar right)
{
    CATCH_TENSOR(left->remainder_(*right));
}

Tensor THSTensor_remainderS2(const Scalar left, const Tensor right)
{
    CATCH_TENSOR(at::empty(right->sizes(), right->options()).fill_(*left).remainder_(*right));
}

Tensor THSTensor_sigmoid(const Tensor tensor)
{
    CATCH_TENSOR(tensor->sigmoid());
}

Tensor THSTensor_sub(const Tensor left, const Tensor right)
{
    CATCH_TENSOR(left->sub(*right));
}

Tensor THSTensor_sub_(const Tensor left, const Tensor right)
{
    CATCH_TENSOR(left->sub_(*right));
}

Tensor THSTensor_subS(const Tensor left, const Scalar right)
{
    CATCH_TENSOR(left->sub(*right));
}

Tensor THSTensor_subS2(const Scalar left, const Tensor right)
{
    CATCH_TENSOR(at::empty(right->sizes(), right->options()).fill_(*left).sub_(*right));
}

Tensor THSTensor_subS_(const Tensor left, const Scalar right)
{
    CATCH_TENSOR(left->sub_(*right));
}

Tensor THSTensor_sum(const Tensor tensor, bool has_type, const int8_t dtype)
{
    CATCH_TENSOR(has_type? tensor->sum((c10::ScalarType)dtype) : tensor->sum())
}

Tensor THSTensor_sum1(const Tensor tensor, const int64_t * dimensions, int length, bool keep_dimension, bool has_type, const int8_t dtype)
{
    CATCH_TENSOR(
        has_type ?
            tensor->sum(at::ArrayRef<int64_t>(dimensions, length), keep_dimension, (c10::ScalarType)dtype)
        :
            tensor->sum(at::ArrayRef<int64_t>(dimensions, length), keep_dimension))
}

Tensor THSTensor_unsqueeze(Tensor tensor, int64_t dimension)
{
    CATCH_TENSOR(tensor->unsqueeze(dimension))
}

Tensor THSTensor_expand(const Tensor tensor, const int64_t* sizes, const int length, bool implicit)
{
    CATCH_TENSOR(tensor->expand(at::ArrayRef<int64_t>(sizes, length), implicit));
}

Tensor THSTensor_flip(const Tensor tensor, const int64_t* sizes, const int length)
{
    CATCH_TENSOR(tensor->flip(at::ArrayRef<int64_t>(sizes, length)));
}

Tensor THSTensor_narrow(const Tensor tensor, int64_t dim, int64_t start, int64_t length)
{
    CATCH_TENSOR(tensor->narrow(dim, start, length))
}

Tensor THSTensor_slice(const Tensor tensor, int64_t dim, int64_t start, int64_t finish, int64_t step)
{
    CATCH_TENSOR(tensor->slice(dim, start, finish, step));
}

void THSTensor_unbind(const Tensor tensor, Tensor* (*allocator)(size_t length), const int64_t dimension)
{
    CATCH(
        auto res = tensor->unbind(dimension);
        const size_t sz = res.size();
        Tensor* result = allocator(sz);
        for (size_t i = 0; i < sz; i++)
            result[i] = new torch::Tensor(res[i]);
    )
}

void THSTensor_split_with_sizes(
    const Tensor tensor, 
    Tensor* (*allocator)(size_t length), 
    const int64_t* sizes, 
    const int length, 
    const int64_t dimension)
{
    CATCH(
        auto res = tensor->split_with_sizes(at::ArrayRef<int64_t>(sizes, length), dimension);
        const size_t sz = res.size();
        Tensor* result = allocator(sz);
        for (size_t i = 0; i < sz; i++)
            result[i] = new torch::Tensor(res[i]);
    )
}

Tensor THSTensor_maxpool1d(
    const Tensor tensor,
    const int64_t* kernelSize, const int kernelSizeLength,
    const int64_t* stride, const int strideLength,
    const int64_t* padding, const int paddingLength,
    const int64_t* dilation, const int dilationLength,
    bool ceil_mode)
{
    CATCH_TENSOR(torch::max_pool1d(
        *tensor,
        at::ArrayRef<int64_t>(kernelSize, kernelSizeLength),
        at::ArrayRef<int64_t>(stride, strideLength),
        at::ArrayRef<int64_t>(padding, paddingLength),
        at::ArrayRef<int64_t>(dilation, dilationLength),
        ceil_mode));
}

void THSTensor_maxpool1d_with_indices(
    const Tensor tensor,
    Tensor* (*allocator)(size_t length),
    const int64_t* kernelSize, const int kernelSizeLength,
    const int64_t* stride, const int strideLength,
    const int64_t* padding, const int paddingLength,
    const int64_t* dilation, const int dilationLength,
    bool ceil_mode)
{
    CATCH (
        auto res = torch::max_pool1d_with_indices(
            *tensor,
            at::ArrayRef<int64_t>(kernelSize, kernelSizeLength),
            at::ArrayRef<int64_t>(stride, strideLength),
            at::ArrayRef<int64_t>(padding, paddingLength),
            at::ArrayRef<int64_t>(dilation, dilationLength),
            ceil_mode);
    
        Tensor* result = allocator(2);
        result[0] = new torch::Tensor(std::get<0>(res));
        result[1] = new torch::Tensor(std::get<1>(res));
    )
}

Tensor THSTensor_maxpool2d(
    const Tensor tensor,
    const int64_t* kernelSize, const int kernelSizeLength,
    const int64_t* stride, const int strideLength,
    const int64_t* padding, const int paddingLength,
    const int64_t* dilation, const int dilationLength,
    bool ceil_mode)
{
    CATCH_TENSOR(torch::max_pool2d(
        *tensor, 
        at::ArrayRef<int64_t>(kernelSize, kernelSizeLength),
        at::ArrayRef<int64_t>(stride, strideLength),
        at::ArrayRef<int64_t>(padding, paddingLength),
        at::ArrayRef<int64_t>(dilation, dilationLength)));
}

void THSTensor_maxpool2d_with_indices(
    const Tensor tensor,
    Tensor* (*allocator)(size_t length),
    const int64_t* kernelSize, const int kernelSizeLength,
    const int64_t* stride, const int strideLength,
    const int64_t* padding, const int paddingLength,
    const int64_t* dilation, const int dilationLength,
    bool ceil_mode)
{
    CATCH(
        auto res = torch::max_pool2d_with_indices(
            *tensor,
            at::ArrayRef<int64_t>(kernelSize, kernelSizeLength),
            at::ArrayRef<int64_t>(stride, strideLength),
            at::ArrayRef<int64_t>(padding, paddingLength),
            at::ArrayRef<int64_t>(dilation, dilationLength),
            ceil_mode);
        Tensor* result = allocator(2);
        result[0] = new torch::Tensor(std::get<0>(res));
        result[1] = new torch::Tensor(std::get<1>(res));
    )
}

Tensor THSTensor_maxpool3d(
    const Tensor tensor,
    const int64_t* kernelSize, const int kernelSizeLength,
    const int64_t* stride, const int strideLength,
    const int64_t* padding, const int paddingLength,
    const int64_t* dilation, const int dilationLength,
    bool ceil_mode)
{
    CATCH_TENSOR(torch::max_pool3d(
            *tensor,
            at::ArrayRef<int64_t>(kernelSize, kernelSizeLength),
            at::ArrayRef<int64_t>(stride, strideLength),
            at::ArrayRef<int64_t>(padding, paddingLength),
            at::ArrayRef<int64_t>(dilation, dilationLength),
            ceil_mode));
}

void THSTensor_maxpool3d_with_indices(
    const Tensor tensor,
    Tensor* (*allocator)(size_t length),
    const int64_t* kernelSize, const int kernelSizeLength,
    const int64_t* stride, const int strideLength,
    const int64_t* padding, const int paddingLength,
    const int64_t* dilation, const int dilationLength,
    bool ceil_mode)
{
    CATCH(
        auto res = torch::max_pool3d_with_indices(
            *tensor,
            at::ArrayRef<int64_t>(kernelSize, kernelSizeLength),
            at::ArrayRef<int64_t>(stride, strideLength),
            at::ArrayRef<int64_t>(padding, paddingLength),
            at::ArrayRef<int64_t>(dilation, dilationLength),
            ceil_mode);
        Tensor* result = allocator(2);
        result[0] = new torch::Tensor(std::get<0>(res));
        result[1] = new torch::Tensor(std::get<1>(res));
    )
}

Tensor THSTensor_maxunpool2d(
    const Tensor tensor,
    const Tensor indices,
    const int64_t* outputSize, const int outputSizeLength)
{
    CATCH_TENSOR(torch::max_unpool2d(
        *tensor,
        *indices,
        at::ArrayRef<int64_t>(outputSize, outputSizeLength)));
}

Tensor THSTensor_maxunpool3d(
    const Tensor tensor,
    const Tensor indices,
    const int64_t* outputSize, const int outputSizeLength,
    const int64_t* stride, const int strideLength,
    const int64_t* padding, const int paddingLength)
{
    CATCH_TENSOR(torch::max_unpool3d(
        *tensor,
        *indices,
        at::ArrayRef<int64_t>(outputSize, outputSizeLength),
        at::ArrayRef<int64_t>(stride, strideLength),
        at::ArrayRef<int64_t>(padding, paddingLength)));
}

Tensor THSTensor_conv_transpose1d(
    const Tensor input, const Tensor weight, const Tensor bias,
    const int64_t* stride, const int strideLength,
    const int64_t* padding, const int paddingLength,
    const int64_t* outputPadding, const int outputPaddingLength,
    const int64_t* dilation, const int dilationLength,
    int64_t groups)
{
    CATCH_TENSOR(torch::conv_transpose1d(*input, *weight, (bias ? *bias : at::Tensor()),
            at::ArrayRef<int64_t>(stride, strideLength),
            at::ArrayRef<int64_t>(padding, paddingLength),
            at::ArrayRef<int64_t>(outputPadding, outputPaddingLength),
            groups,
            at::ArrayRef<int64_t>(dilation, dilationLength)));
}

Tensor THSTensor_conv_transpose2d(
    const Tensor input, const Tensor weight, const Tensor bias,
    const int64_t* stride, const int strideLength,
    const int64_t* padding, const int paddingLength,
    const int64_t* outputPadding, const int outputPaddingLength,
    const int64_t* dilation, const int dilationLength,
    int64_t groups)
{
    CATCH_TENSOR(torch::conv_transpose2d(*input, *weight, (bias ? *bias : at::Tensor()),
            at::ArrayRef<int64_t>(stride, strideLength),
            at::ArrayRef<int64_t>(padding, paddingLength),
            at::ArrayRef<int64_t>(outputPadding, outputPaddingLength),
            groups,
            at::ArrayRef<int64_t>(dilation, dilationLength)));
}

Tensor THSTensor_conv_transpose3d(
    const Tensor input, const Tensor weight, const Tensor bias,
    const int64_t* stride, const int strideLength,
    const int64_t* padding, const int paddingLength,
    const int64_t* outputPadding, const int outputPaddingLength,
    const int64_t* dilation, const int dilationLength,
    int64_t groups)
{
    CATCH_TENSOR(torch::conv_transpose3d(*input, *weight, (bias ? *bias : at::Tensor()),
            at::ArrayRef<int64_t>(stride, strideLength),
            at::ArrayRef<int64_t>(padding, paddingLength),
            at::ArrayRef<int64_t>(outputPadding, outputPaddingLength),
            groups,
            at::ArrayRef<int64_t>(dilation, dilationLength)));
}

Tensor THSTensor_conv1d(
    const Tensor input, 
    const Tensor weight, 
    const Tensor bias,
    const int64_t* stride, const int strideLength,
    const int64_t* padding, const int paddingLength,
    const int64_t* dilation, const int dilationLength,
    int64_t groups)
{
    CATCH_TENSOR(torch::conv1d(*input, *weight, (bias ? *bias : at::Tensor()),
            at::ArrayRef<int64_t>(stride, strideLength),
            at::ArrayRef<int64_t>(padding, paddingLength),
            at::ArrayRef<int64_t>(dilation, dilationLength),
            groups));
}

Tensor THSTensor_conv2d(
    const Tensor input, 
    const Tensor weight, 
    const Tensor bias,
    const int64_t* stride, const int strideLength,
    const int64_t* padding, const int paddingLength,
    const int64_t* dilation, const int dilationLength,
    int64_t groups)
{
    CATCH_TENSOR(torch::conv2d(*input, *weight, (bias ? *bias : at::Tensor()),
            at::ArrayRef<int64_t>(stride, strideLength),
            at::ArrayRef<int64_t>(padding, paddingLength),
            at::ArrayRef<int64_t>(dilation, dilationLength),
            groups));
}

Tensor THSTensor_conv3d(
    const Tensor input, 
    const Tensor weight, 
    const Tensor bias,
    const int64_t* stride, const int strideLength,
    const int64_t* padding, const int paddingLength,
    const int64_t* dilation, const int dilationLength,
    int64_t groups)
{
    CATCH_TENSOR(torch::conv3d(*input, *weight, (bias ? *bias : at::Tensor()),
            at::ArrayRef<int64_t>(stride, strideLength),
            at::ArrayRef<int64_t>(padding, paddingLength),
            at::ArrayRef<int64_t>(dilation, dilationLength),
            groups));
}

Tensor THSTensor_gather(
    const Tensor tensor,
    const int64_t dimension,
    const Tensor index)
{
    CATCH_TENSOR(torch::gather(*tensor, dimension, *index));
}

Tensor THSTensor_scatter(
    const Tensor tensor,
    const int64_t dimension,
    const Tensor index,
    const Tensor source)
{
    CATCH_TENSOR(torch::scatter(*tensor, dimension, *index, *source));
}
